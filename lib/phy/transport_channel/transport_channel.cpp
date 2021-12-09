/*
 * Copyright 2020-2021 Telecom Paris

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 */

#include "transport_channel.h"

#include <cmath>

#include <algorithm>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <thread>
#include <vector>

#include "../../asn1c/nr_rrc/BCCH-DL-SCH-Message.h"
#include "../../utils/common_utils/common_utils.h"
#include "../../utils/sequence_generator/sequence_generator.h"
#include "../../variables/common_matrices/common_matrices.h"
#include "../../variables/common_variables/common_variables.h"
#include "../../variables/ldpc_matrices/ldpc_matrices.h"
#include "../libphy/libphy.h"

using namespace std;

auto free5GRAN::phy::transport_channel::compute_N_polar_code(int E,
                                                             int K,
                                                             int nmax) -> int {
  /**
   * \fn compute_N_polar_code
   * \brief Compute polar coding out sequence size
   * \standard TS 38.212 V15.2.0 Section 5.3.1
   *
   * \param[in] E: Rate matching output sequence length
   * \param[in] K: Polar coding input sequence length (including CRC)
   * \param[in] nmax: Maximum value of n
   *
   * \return Polar coding out sequence size
   */
  int n1, n2;
  float rmin = 1.0 / 8.0;
  if (E <= (9.0 / 8.0) * pow(2, ceil(log2(E)) - 1) &&
      (float)K / (float)E < 9.0 / 16.0) {
    n1 = ceil(log2(E)) - 1;
  } else {
    n1 = ceil(log2(E));
  }
  n2 = ceil(log2((float)K / rmin));
  if (nmax < 5 && n1 < 5 && n2 < 5) {
    return 5;
  } else {
    if (n1 < n2 && n1 < nmax) {
      return n1;
    } else if (n2 < n1 && n2 < nmax) {
      return n2;
    } else {
      return nmax;
    }
  }
}

void free5GRAN::phy::transport_channel::rate_recover(int* input_bits,
                                                     int* output_bits,
                                                     int i_bil,
                                                     int E,
                                                     int N,
                                                     int K) {
  /**
   * \fn rate_recover
   * \brief Rate recovering for polar coding.
   * \standard TS 38.212 V15.2.0 Section 5.4.1
   *
   * \partial_imp Code block de-interleaving not implemented
   * \param[in] input_bits: Input bits sequence
   * \param[out] output_bits: Output bits sequence
   * \param[in] i_bil: Coded blocks interleaving indicator (0: No interleaving,
   * 1: Interleaving) \param[in] E: Rate matching output sequence length
   * \param[in] N: Rate matching input sequence length
   */
  int e[E], y[N];
  /*
   * Coded bit-interleaving/de-interleaving TS38.212 5.4.1.3
   * No coded-bits interleaving
   */
  if (i_bil == 0) {
    for (int n = 0; n < E; n++) {
      e[n] = input_bits[n];
    }
  }
  /*
   * Bit de-selection TS38.212 5.4.1.2
   */
  if (E >= N) {
    for (int n = 0; n < N; n++) {
      y[n] = e[n];
    }
  } else {
    if ((float)K / (float)E <= 7.0 / 16.0) {
      for (int n = 0; n < N - E; n++) {
        y[n] = 0;
      }
      for (int n = 0; n < E; n++) {
        y[n + N - E] = e[n];
      }
    }
  }

  /*
   * Sub-block de-interleaving TS38.212 5.4.1.1
   */
  for (int n = 0; n < N; n++) {
    int i = floor(32 * (double)n / (double)N);
    int j_n =
        free5GRAN::SUB_BLOCK_INTERLEAVER_PATTERN[i] * N / 32 + n % (N / 32);
    output_bits[j_n] = y[n];
  }
}

void free5GRAN::phy::transport_channel::polar_decode(int* input_bits,
                                                     int* output_bits,
                                                     int N,
                                                     int K,
                                                     int nmax,
                                                     int i_il,
                                                     int n_pc,
                                                     int n_wm_pc,
                                                     int E) {
  /**
   * \fn polar_decode
   * \brief Polar decoding
   * \standard TS 38.212 V15.2.0 Section 5.3.1
   *
   * \partial_imp Only n_wm_pc=0 is implemented
   * \details
   * Details:
   * - Polar decoding using Gn inverse matrix
   * - Computing required sets
   * - Recover c'
   * - De-interleave c' to recover output
   *
   * \param[in] input_bits: Input bits sequence
   * \param[out] output_bits: Output bits sequence
   * \param[in] N: Rate matching input sequence length
   * \param[in] K: Polar coding input sequence length (including CRC)
   * \param[in] nmax: Maximum value of n
   * \param[in] i_il: Interleaving indicator (0: No interleaving, 1:
   * Interleaving) \param[in] n_pc: Number of parity check bits \param[in]
   * n_wm_pc: Number of other parity check bits
   */
  int q_0_n_1[N], count_seq, q_i_n[K + n_pc], c_p[K], pi_seq[K], j_n, u[N];
  int K_max = 164;
  bool found;

  /*
   * polar decoding using Gn inverse matrix (TS38.212 5.3.1.2)
   */
  switch (N) {
    case 32: {
      for (int n = 0; n < N; n++) {
        u[n] = 0;
        for (int p = 0; p < N; p++) {
          u[n] ^= (input_bits[p] * free5GRAN::G5_INV[p][n]);
        }
      }
    };
    case 64: {
      for (int n = 0; n < N; n++) {
        u[n] = 0;
        for (int p = 0; p < N; p++) {
          u[n] ^= (input_bits[p] * free5GRAN::G6_INV[p][n]);
        }
      }
    };
    case 128: {
      for (int n = 0; n < N; n++) {
        u[n] = 0;
        for (int p = 0; p < N; p++) {
          u[n] ^= (input_bits[p] * free5GRAN::G7_INV[p][n]);
        }
      }
    };
    case 256: {
      for (int n = 0; n < N; n++) {
        u[n] = 0;
        for (int p = 0; p < N; p++) {
          u[n] ^= (input_bits[p] * free5GRAN::G8_INV[p][n]);
        }
      }
    };
    case 512: {
      for (int n = 0; n < N; n++) {
        u[n] = 0;
        for (int p = 0; p < N; p++) {
          u[n] ^= (input_bits[p] * free5GRAN::G9_INV[p][n]);
        }
      }
    };
    case 1024: {
      for (int n = 0; n < N; n++) {
        u[n] = 0;
        for (int p = 0; p < N; p++) {
          u[n] ^= (input_bits[p] * free5GRAN::G10_INV[p][n]);
        }
      }
    };
  }

  count_seq = 0;
  vector<int> q_ftmp_n, q_itmp_n;

  /*
   * Computing q_0_n_1 (TS38.212 5.3.1.2)
   */
  for (int n : free5GRAN::POLAR_SEQUENCE_QNMAX_AND_RELIABILITY) {
    if (n < N) {
      q_0_n_1[count_seq] = n;
      count_seq++;
    }
  }

  if (E < N) {
    if ((float)K / (float)E <= 7.0 / 16.0) {
      for (int n = 0; n < N - E; n++) {
        int i = floor(32 * (double)n / (double)N);
        j_n =
            free5GRAN::SUB_BLOCK_INTERLEAVER_PATTERN[i] * N / 32 + n % (N / 32);
        q_ftmp_n.push_back(j_n);
      }
      if (E >= 3.0 * (float)N / 4.0) {
        for (int n = 0; n < ceil(3.0 * (float)N / 4.0 - (float)E / 2.0); n++) {
          q_ftmp_n.push_back(n);
        }
      } else {
        for (int n = 0; n < ceil(9.0 * (float)N / 16.0 - (float)E / 4.0); n++) {
          q_ftmp_n.push_back(n);
        }
      }
    }
  }

  for (int n = 0; n < N; n++) {
    found = false;
    for (int x : q_ftmp_n) {
      if (q_0_n_1[n] == x) {
        found = true;
        break;
      }
    }
    if (!found) {
      q_itmp_n.push_back(q_0_n_1[n]);
    }
  }
  /*
   * Computing q_i_n (TS38.212 5.3.1.2)
   */
  for (int n = 0; n < K + n_pc; n++) {
    q_i_n[n] = q_itmp_n[q_itmp_n.size() - (K + n_pc) + n];
  }
  count_seq = 0;
  /*
   * Recovering c' from u_n (TS38.212 5.3.1.2)
   */
  for (int n = 0; n < N; n++) {
    found = false;
    for (int p = 0; p < K + n_pc; p++) {
      if (q_i_n[p] == n) {
        found = true;
        break;
      }
    }
    if (found) {
      c_p[count_seq] = u[n];
      count_seq++;
    }
  }
  count_seq = 0;
  /*
   * generating pi sequence (TS38.212 5.3.1.1)
   */
  for (int m = 0; m < K_max; m++) {
    if (free5GRAN::INTERLEAVING_PATTERN[m] >= K_max - K) {
      pi_seq[count_seq] = free5GRAN::INTERLEAVING_PATTERN[m] - (K_max - K);
      count_seq++;
    }
  }
  /*
   * de-interleaving c' to recover output sequence (TS38.212 5.3.1.1)
   */
  for (int k = 0; k < K; k++) {
    output_bits[pi_seq[k]] = c_p[k];
  }
}

void free5GRAN::phy::transport_channel::crc_validate(int* input_bits,
                                                     int* crc_polynom,
                                                     int* remainder,
                                                     int length_input,
                                                     int length_crc) {
  /**
   * \fn crc_validate
   * \brief CRC validation
   * \details
   * Computes the remainder of the division of the input sequence by the
   * polynom. If the remainder is equal to 0, CRC is validated
   *
   * \param[in] input_bits: Input bits sequence
   * \param[in] crc_polynom: Polynom used for CRC computation
   * \param[out] remainder: Output remainder of the division
   * \param[in] length_input: Input size
   * \param[in] length_crc: Polynom size
   */
  int num_steps, seq1[length_crc];

  /*
   * Getting index of first 1 in input_bits
   */
  int index_0 = -1;
  for (int i = 0; i < length_input; i++) {
    if (input_bits[i] == 1) {
      index_0 = i;
      break;
    }
  }
  /*
   * Creating a new input called temp_input by removing all 0 from the beginning
   * of input_bits
   */
  int temp_input[length_input - index_0];
  for (int i = 0; i < length_input - index_0; i++) {
    temp_input[i] = input_bits[index_0 + i];
  }
  length_input = length_input - index_0;
  num_steps = length_input - length_crc + 1;

  /*
   * seq1 is the variable that will be XORed with crc_polynom step after step
   * Initializing seq1 variable to the first bits of temp_input
   */
  for (int i = 0; i < length_crc; i++) {
    seq1[i] = temp_input[i];
  }

  int i = 0;

  /*
   * Iterate until the polynom reaches the end of temp_input
   */
  while (i < num_steps) {
    /*
     * XORing seq1 and crc_polynom
     */
    for (int j = 0; j < length_crc; j++) {
      remainder[j] = seq1[j] ^ crc_polynom[j];
    }
    /*
     * Checing if the remainder is equal to 0. If true, algorithm ends
     */
    bool validated = true;
    for (int j = 1; j < length_crc; j++) {
      if (remainder[j] == 1) {
        validated = false;
        break;
      }
    }
    if (validated) {
      break;
    }
    /*
     * Searching first 1 index in remainder
     */
    int index_1 = -1;
    for (int j = 1; j < length_crc; j++) {
      if (remainder[j] == 1) {
        index_1 = j;
        break;
      }
    }
    /*
     * seq1 is updated to be the remainder shifted until finding the first 1
     */
    for (int j = 0; j < length_crc - index_1; j++) {
      seq1[j] = remainder[j + index_1];
    }
    /*
     * Adding new entries from temp_input to fill seq1
     */
    for (int j = 0; j < index_1; j++) {
      seq1[length_crc - index_1 + j] = temp_input[length_crc + i + j];
    }
    i += index_1;
  }
}

void free5GRAN::phy::transport_channel::compute_crc(int* input_bits,
                                                    int* crc_polynom,
                                                    int* remainder,
                                                    int length_input,
                                                    int length_crc) {
  /**
   * \fn compute_crc
   * \brief CRC computation
   * \details
   * Compute the CRC for a given input and polynom
   *
   * \param[in] input_bits: Input bits sequence
   * \param[in] crc_polynom: Polynom used for CRC computation
   * \param[out] remainder: Output CRC
   * \param[in] length_input: Input size
   * \param[in] length_crc: Polynom size
   */
  int num_steps, *seq1;

  /*
   * Getting index of first 1 in input_bits
   */
  int index_0 = -1;
  for (int i = 0; i < length_input; i++) {
    if (input_bits[i] == 1) {
      index_0 = i;
      break;
    }
  }
  /*
   * Creating a new input called temp_input by removing all 0 from the beginning
   * of input_bits Adding (length_crc - 1) zeros to complete temp_input
   */
  int temp_input[length_input - index_0 + length_crc - 1];
  for (int i = 0; i < length_input - index_0; i++) {
    temp_input[i] = input_bits[index_0 + i];
  }
  for (int i = 0; i < length_crc - 1; i++) {
    temp_input[length_input - index_0 + i] = 0;
  }
  length_input = length_input - index_0;
  num_steps = length_input;

  /*
   * Iterate until the polynom reaches the end of temp_input
   */
  int i = 0;
  while (i < num_steps) {
    /*
     * XORing temp_input and crc_polynom
     */
    for (int j = 0; j < length_crc; j++) {
      temp_input[i + j] ^= crc_polynom[j];
    }
    /*
     * Checing if temp_input (for the first length_input bits) is equal to 0. If
     * true, algorithm ends
     */
    bool finished = true;
    for (int j = 0; j < length_input; j++) {
      if (temp_input[j] == 1) {
        finished = false;
        break;
      }
    }
    if (finished) {
      break;
    }
    /*
     * Shifting until finding a 1 (at least once)
     */
    i++;
    while (temp_input[i] != 1) {
      i++;
    }
  }
  /*
   * Remainder corresponds to the (length_crc - 1) last bits of temp_input
   */
  for (int j = 0; j < length_crc - 1; j++) {
    remainder[j] = temp_input[length_input + j];
  }
}

void free5GRAN::phy::transport_channel::compute_ldpc_base_graph(int A,
                                                                float R,
                                                                int& graph) {
  /**
   * \fn compute_ldpc_base_graph
   * \brief Choose LDPC base graph
   * \standard TS 38.212 V15.2.0 Section 7.2.2
   *
   * \param[in] A: Transport block size
   * \param[in] R: Code rate
   * \param[out] graph: Output graph
   */
  if (A <= 292 || (A <= 3824 && R <= 0.67) || R <= 0.25) {
    graph = 2;
  } else {
    graph = 1;
  }
}

void free5GRAN::phy::transport_channel::compute_transport_block_size(
    int n_re,
    float R,
    int mod_order,
    int num_layers,
    int nrb,
    int& tbs) {
  /**
   * \fn compute_transport_block_size
   * \brief Transport block size computation
   * \standard TS 38.214 V15.2.0 Section 5.1.3.2
   *
   * \partial_imp n_info > 3824 not implemented
   *
   * \param[in] n_re: Number of PDSCH RE per RB
   * \param[in] R: Code rate
   * \param[in] mod_order: Modulation order
   * \param[in] num_layers: Number of transport layers
   * \param[in] nrb: Number of RB in PDSCH allocation
   * \param[out] tbs: Transport block size
   */
  long nre = (long)min(156, n_re) * nrb;
  double n_info = (double)nre * R * mod_order * num_layers;
  if (n_info <= 3824) {
    long n = (int)max(3.0, floor(log2(n_info)) - 6);
    long n_p_info = max(24.0, pow(2, n) * floor((double)n_info / pow(2, n)));
    for (int i : free5GRAN::TS_38_214_TABLE_5_1_3_2_1) {
      if (i >= n_p_info) {
        tbs = i;
        break;
      }
    }
  } else {
    cout << "N INFO not supported !" << endl;
  }
}

/*
 * TS 38 212 5.2.2
 */
void free5GRAN::phy::transport_channel::compute_Zc_dl_sch(int kb,
                                                          float k_p,
                                                          int& Zc,
                                                          int& i_ls) {
  /**
   * \fn compute_Zc_dl_sch
   * \brief Compute LDPC lifting size for DL-SCH encoding/decoding
   * \standard TS 38.212 V15.2.0 Section 5.2.2
   *
   * \param[in] kb: Intermediate value for Zc computation
   * \param[in] k_p: K' value
   * \param[out] Zc: Returned value
   * \param[out] i_ls: Zc set index
   */
  Zc = 512;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (TS_38_212_TABLE_5_3_2_1[i][j] < Zc &&
          TS_38_212_TABLE_5_3_2_1[i][j] >= (k_p / (float)kb)) {
        Zc = TS_38_212_TABLE_5_3_2_1[i][j];
        i_ls = i;
      }
    }
  }
}

void free5GRAN::phy::transport_channel::
    compute_code_block_segmentation_info_ldpc(int graph,
                                              int B,
                                              int& Zc,
                                              int& K,
                                              int& i_ls,
                                              int& L,
                                              int& C,
                                              int& N,
                                              int& K_p) {
  /**
   * \fn compute_code_block_segmentation_info_ldpc
   * \brief Compute code block segmentation informations for LDPC
   * \standard TS 38.212 V15.2.0 Section 5.2.2
   *
   * \param[in] graph: LDPC base graph
   * \param[in] B: Code block segmentation input size (inlcuding CRC)
   * \param[out] Zc: Returned LDPC lifting size
   * \param[out] K: Code block segmentation output size
   * \param[out] i_ls: Zc set index
   * \param[out] L: Code block CRC length
   * \param[out] C: Number of code blocks
   * \param[out] N: LDPC output sequence
   * \param[out] K_p: K' intermediate K value
   */
  int k_b, B_p;
  int k_cb = (graph == 1) ? 8448 : 3840;
  if (B <= k_cb) {
    L = 0;
    C = 1;
    B_p = B;
  } else {
    L = 24;
    C = ceil(B / (k_cb - L));
    B_p = B + C * L;
  }
  float k_p = (float)B_p / (float)C;
  if (graph == 1) {
    k_b = 22;
  } else {
    if (B > 640) {
      k_b = 10;
    } else if (B > 560) {
      k_b = 9;
    } else if (B > 192) {
      k_b = 8;
    } else {
      k_b = 6;
    }
  }
  compute_Zc_dl_sch(k_b, k_p, Zc, i_ls);
  K = (graph == 1) ? 22 * Zc : 10 * Zc;
  N = (graph == 1) ? 66 * Zc : 50 * Zc;
  K_p = (int)k_p;
}

void free5GRAN::phy::transport_channel::rate_recover_ldpc(
    int* input_bits,
    int N,
    int i_lbrm,
    int E,
    int id_rv,
    int mod_order,
    int C,
    int Zc,
    int graph,
    int K,
    int K_p,
    int* output_sequence) {
  /**
   * \fn rate_recover_ldpc
   * \brief Rate recovering for LDPC (hard bits)
   * \standard TS 38.212 V15.2.0 Section 5.4.2
   *
   * \param[in] input_bits: DL-SCH input bits
   * \param[in] N: Output sequence length
   * \param[in] i_lbrm: Indicator for N_cb computation
   * \param[in] E: DL-SCH input sequence length
   * \param[in] id_rv: Redundancy version
   * \param[in] mod_order: Modulation order
   * \param[in] C: Number of code blocks
   * \param[in] Zc: LDPC lifting size
   * \param[in] graph: LDPC base graph
   * \param[in] K: Code block length
   * \param[in] K_p: K' code block intermediate length
   * \param[out] output_sequence: Output bits
   */
  int N_cb = (i_lbrm == 0) ? N : min(N, 25344);
  int e[E];
  int E_Q = (int)((float)E / (float)mod_order);
  /*
   * Input de-interleaving
   */
  for (int j = 0; j < E_Q; j++) {
    for (int i = 0; i < mod_order; i++) {
      e[i * (E_Q) + j] = input_bits[i + j * mod_order];
    }
  }
  /*
   * Compute k0
   */
  int k0, k, j;
  if (id_rv == 0) {
    k0 = 0;
  } else if (id_rv == 1) {
    k0 = (graph == 1) ? floor((17.0 * N_cb) / (66.0 * Zc)) * Zc
                      : floor((13.0 * N_cb) / (50.0 * Zc)) * Zc;
  } else if (id_rv == 2) {
    k0 = (graph == 1) ? floor((33.0 * N_cb) / (66.0 * Zc)) * Zc
                      : floor((25.0 * N_cb) / (50.0 * Zc)) * Zc;
  } else if (id_rv == 3) {
    k0 = (graph == 1) ? floor((56.0 * N_cb) / (66.0 * Zc)) * Zc
                      : floor((43.0 * N_cb) / (50.0 * Zc)) * Zc;
  }

  /*
   * rate recovering
   */
  j = 0;
  k = 0;
  while (k < E) {
    int index = (k0 + j) % N_cb;
    if (index >= K_p - 2 * Zc && index < K - 2 * Zc) {
      output_sequence[index] = -1;
    } else {
      output_sequence[index] = e[k];
      k++;
    }
    j++;
  }
}

void free5GRAN::phy::transport_channel::rate_recover_ldpc(
    double* input_bits,
    int N,
    int i_lbrm,
    int E,
    int id_rv,
    int mod_order,
    int C,
    int Zc,
    int graph,
    int K,
    int K_p,
    double* output_sequence) {
  /**
   * \fn rate_recover_ldpc
   * \brief Rate recovering for LDPC (soft bits)
   * \standard TS 38.212 V15.2.0 Section 5.4.2
   *
   * \param[in] input_bits: DL-SCH input soft bits
   * \param[in] N: Output sequence length
   * \param[in] i_lbrm: Indicator for N_cb computation
   * \param[in] E: DL-SCH input sequence length
   * \param[in] id_rv: Redundancy version
   * \param[in] mod_order: Modulation order
   * \param[in] C: Number of code blocks
   * \param[in] Zc: LDPC lifting size
   * \param[in] graph: LDPC base graph
   * \param[in] K: Code block length
   * \param[in] K_p: K' code block intermediate length
   * \param[out] output_sequence: Output soft bits
   */
  int N_cb = (i_lbrm == 0) ? N : min(N, 25344);
  double e[E];
  int E_Q = (int)((float)E / (float)mod_order);
  /*
   * Input de-interleaving
   */
  for (int j = 0; j < E_Q; j++) {
    for (int i = 0; i < mod_order; i++) {
      e[i * (E_Q) + j] = input_bits[i + j * mod_order];
    }
  }

  int k0, k, index, j;
  if (id_rv == 0) {
    k0 = 0;
  } else if (id_rv == 1) {
    k0 = (graph == 1) ? floor((17.0 * N_cb) / (66.0 * Zc)) * Zc
                      : floor((13.0 * N_cb) / (50.0 * Zc)) * Zc;
  } else if (id_rv == 2) {
    k0 = (graph == 1) ? floor((33.0 * N_cb) / (66.0 * Zc)) * Zc
                      : floor((25.0 * N_cb) / (50.0 * Zc)) * Zc;
  } else if (id_rv == 3) {
    k0 = (graph == 1) ? floor((56.0 * N_cb) / (66.0 * Zc)) * Zc
                      : floor((43.0 * N_cb) / (50.0 * Zc)) * Zc;
  }

  vector<int> seen_indexes;
  /*
   * rate recovering
   */
  j = 0;
  k = 0;
  while(k < E && j<N_cb){
    index = (k0 + j) % N_cb;
    if (find(seen_indexes.begin(), seen_indexes.end(), index) ==
        seen_indexes.end()) {
      seen_indexes.push_back(index);
      if (index >= K_p - 2 * Zc && index < K - 2 * Zc) {
        output_sequence[index] = numeric_limits<double>::infinity();
        ;
      } else {
        output_sequence[index] = e[k];
        k++;
      }
    }
    j++;
  }
}

void free5GRAN::phy::transport_channel::compute_circular_permutation_matrix(
    int size,
    int offset,
    int** matrix) {
  /**
   * \fn compute_circular_permutation_matrix
   * \brief Compute offset times right shifted identity matrix of size n
   * \param[in] size: Identity matrix size
   * \param[in] offset: Number of times to shift matrix
   * \param[out] matrix: Output matrix
   */
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      matrix[i][j] = 0;
    }
    matrix[i][(i + offset) % size] = 1;
  }
}

void free5GRAN::phy::transport_channel::ldpc_decode_one_bit(
    vector<vector<int>> R,
    double* soft_bits,
    int i,
    double& new_bit) {
  /**
   * \fn ldpc_decode_one_bit
   * \brief LDPC correct one bit value (using belief propagation algorithm)
   * \param[in] R: Input set of rows connected to bit i
   * \param[in] soft_bits: Input soft bits
   * \param[in] i: Bit index
   * \param[out] new_bit: New bit value
   */
  double r_p1[R.size()], r_prop, q_p1, q_m1, n_q_p1, n_q_m1;
  /*
   * Compute rj for each element in R
   */
  for (int j = 0; j < R.size(); j++) {
    r_p1[j] = 1;
    for (int i_p = 0; i_p < R[j].size(); i_p++) {
      r_prop = 1 / (1 + exp(2 * soft_bits[R[j][i_p]]));
      r_p1[j] *= 1 - 2 * r_prop;
    }
    r_p1[j] = 0.5 + 0.5 * r_p1[j];
  }
  /*
   * Compute updated bit probabilities
   */
  q_m1 = 1;
  q_p1 = 1;
  for (int j = 0; j < R.size(); j++) {
    q_p1 *= r_p1[j];
    q_m1 *= (1 - r_p1[j]);
  }
  r_prop = 1 / (1 + exp(2 * soft_bits[i]));
  q_m1 = r_prop * q_m1;
  q_p1 = (1 - r_prop) * q_p1;
  /*
   * Normalization
   */
  n_q_p1 = q_p1 / (q_p1 + q_m1);
  n_q_m1 = q_m1 / (q_p1 + q_m1);
  /*
   * Update bit value depending on max probability
   */
  if (n_q_p1 > n_q_m1) {
    new_bit = -0.5 * log((1 / n_q_p1) - 1);
  } else {
    new_bit = 0.5 * log((1 / n_q_m1) - 1);
  }
}

void free5GRAN::phy::transport_channel::compute_H_matrix_ldpc(
    int Zc,
    int graph,
    int i_ls,
    vector<vector<int>>& matrix,
    int& size_i,
    int& size_j) {
  /**
   * \fn compute_H_matrix_ldpc
   * \brief Compute Hbg matrix for LDPC
   * \standard TS 38.212 V15.2.0 Section 5.3.2
   *
   * \param[in] Zc: LDPC lifting size
   * \param[in] graph: LDPC base graph
   * \param[in] i_ls: Zc set index
   * \param[out] matrix: H matrix
   * \param[out] size_i: H matrix number of rows
   * \param[out] size_i: H matrix number of columns
   */
  if (graph == 1) {
    size_i = 46;
    size_j = 68;
  } else {
    size_i = 42;
    size_j = 52;
  }

  vector<int*> ldpc_table;
  if (graph == 1) {
    ldpc_table = free5GRAN::TS_38_212_TABLE_5_3_2_2;
  } else {
    ldpc_table = free5GRAN::TS_38_212_TABLE_5_3_2_3;
  }
  for (auto& p : ldpc_table) {
    int index_i = p[0];
    int index_j = p[1];
    int v_ij = p[i_ls + 2];
    matrix[index_i][index_j] = v_ij;
  }
}

void free5GRAN::phy::transport_channel::ldpc_decode(double* input_bits,
                                                    int N,
                                                    int Zc,
                                                    int graph,
                                                    int K,
                                                    int i_ls,
                                                    int* output_sequence) {
  /**
   * \fn compute_H_matrix_ldpc
   * \brief Compute H matrix for LDPC using Belief propagation algorithm
   * \standard TS 38.212 V15.2.0 Section 5.3.2
   *
   * \details
   * Details:
   * - Compute H matrix
   * - Recover LDPC input bits from input sequence
   * - Compute columns and row bit relations
   * - Iterate 10 time:
   * -# Try to correct each input bit value
   * -# If H times corrected bits value equals 0, algorithm ends, otherwise it
   * continues
   *
   * \param[in] input_bits: Input soft bits sequence
   * \param[in] N: LDPC input bit sequence length
   * \param[in] Zc: LDPC lifting size
   * \param[in] graph: LDPC base graph
   * \param[in] K: Code block length
   * \param[in] i_ls: Zc set index
   * \param[out] output_sequence: Corrected output bits sequence
   */
  /*
   * H matrix generation
   */
  int size_i, size_j;
  size_i = 52;
  size_j = 42;
  vector<vector<int>> H(size_j, vector<int>(size_i, -1));
  compute_H_matrix_ldpc(Zc, graph, i_ls, H, size_j, size_i);

  double ldpc_input_bits[N + 2 * Zc];
  for (int i = 0; i < 2 * Zc; i++) {
    ldpc_input_bits[i] = 0;
  }
  for (int k = 2 * Zc; k < N + 2 * Zc; k++) {
    ldpc_input_bits[k] = input_bits[k - 2 * Zc];
  }
  double new_bits[N + 2 * Zc];
  vector<vector<int>> R[N + 2 * Zc], R_tot;
  vector<int> new_vec, new_vec_tot;

  /*
   * Generate rows and columns matrices
   */
  for (int j = 0; j < size_j * Zc; j++) {
    new_vec_tot.clear();
    for (int i = 0; i < size_i; i++) {
      if (H[j / Zc][i] != -1) {
        new_vec_tot.push_back(((j % Zc + H[j / Zc][i]) % Zc) + i * Zc);
      }
    }
    R_tot.push_back(new_vec_tot);
  }
  int index_l, inter_ind;
  for (int i = 0; i < N + 2 * Zc; i++) {
    for (int j = 0; j < size_j; j++) {
      if (H[j][i / Zc] != -1) {
        new_vec.clear();
        inter_ind = ((i % Zc - H[j][i / Zc]) % Zc);
        if (inter_ind < 0) {
          inter_ind = Zc + inter_ind;
        }
        index_l = inter_ind + j * Zc;

        for (int& p : R_tot[index_l]) {
          if (p != i) {
            new_vec.push_back(p);
          }
        }
        R[i].push_back(new_vec);
      }
    }
  }
  int rest, final_bit[N + 2 * Zc];
  /*
   * Looping over iteration
   */
  for (int iter = 0; iter < 10; iter++) {
    /*
     * Decode bits
     */
    for (int i = 0; i < N + 2 * Zc; i++) {
      ldpc_decode_one_bit(R[i], &ldpc_input_bits[0], i, ref(new_bits[i]));
    }
    for (int i = 0; i < N + 2 * Zc; i++) {
      ldpc_input_bits[i] = new_bits[i];
      final_bit[i] = (ldpc_input_bits[i] < 0) ? 1 : 0;
      if (i < K) {
        output_sequence[i] = final_bit[i];
      }
    }

    bool validated = true;
    for (int j = 0; j < size_j * Zc; j++) {
      rest = 0;
      for (int i : R_tot[j]) {
        rest ^= final_bit[i];
      }
      if (rest == 1) {
        validated = false;
        break;
      }
    }
    if (validated) {
      BOOST_LOG_TRIVIAL(trace) << "LDPC VALIDATED";
      break;
    }
  }
}

void free5GRAN::phy::transport_channel::decode_bch(int* bch_bits,
                                                   bool& crc_validated,
                                                   int* mib_bits,
                                                   int pci) {
  /**
   * \fn decode_bch
   * \brief Decode broadcast channel
   * \standard TS 38.212 V15.2.0 Section 7.1
   *
   * \details
   * Details:
   * - Rate recovering
   * - Polar decoding
   * - CRC validation
   * - Scrambling
   * - Payload de-interleaving
   *
   * \param[in] bch_bits: Input bits sequence
   * \param[out] crc_validated: Indicator for CRC validation
   * \param[out] mib_bits: Output MIB bits
   * \param[in] pci: Cell PCI
   */
  int n = free5GRAN::phy::transport_channel::compute_N_polar_code(
      free5GRAN::SIZE_SSB_PBCH_SAMPLES * 2, free5GRAN::SIZE_PBCH_POLAR_DECODED,
      9);
  int N = pow(2, n);
  int rate_recovered_bits[N],
      polar_decoded_bits[free5GRAN::SIZE_PBCH_POLAR_DECODED],
      remainder[free5GRAN::BCH_CRC_LENGTH + 1],
      bch_payload[free5GRAN::BCH_PAYLOAD_SIZE],
      bch_crc_recomputed[free5GRAN::BCH_CRC_LENGTH],
      bch_crc[free5GRAN::BCH_CRC_LENGTH], crc_masq[free5GRAN::BCH_CRC_LENGTH];
  // Rate recover bch_bits to rate_recovered_bits
  free5GRAN::phy::transport_channel::rate_recover(
      bch_bits, rate_recovered_bits, 0, free5GRAN::SIZE_SSB_PBCH_SAMPLES * 2, N,
      free5GRAN::SIZE_PBCH_POLAR_DECODED);
  // Polar decode rate_recovered_bits to polar_decoded_bits
  free5GRAN::phy::transport_channel::polar_decode(
      rate_recovered_bits, polar_decoded_bits, N,
      free5GRAN::SIZE_PBCH_POLAR_DECODED, 9, 1, 0, 0,
      free5GRAN::SIZE_SSB_PBCH_SAMPLES * 2);
  // Validate polar_decoded_bits CRC (compute the remainder and check that t is
  // equal to 0)
  free5GRAN::phy::transport_channel::crc_validate(
      polar_decoded_bits, free5GRAN::G_CRC_24_C, remainder,
      free5GRAN::SIZE_PBCH_POLAR_DECODED, free5GRAN::BCH_CRC_LENGTH + 1);
  crc_validated = true;
  for (int i = 1; i < free5GRAN::BCH_CRC_LENGTH + 1; i++) {
    if (remainder[i] == 1) {
      crc_validated = false;
      break;
    }
  }
  // Split polar_decoded_bits into bch_payload and bch_crc
  for (int i = 0; i < free5GRAN::BCH_PAYLOAD_SIZE; i++) {
    bch_payload[i] = polar_decoded_bits[i];
  }
  for (int i = 0; i < free5GRAN::BCH_CRC_LENGTH; i++) {
    bch_crc[i] = polar_decoded_bits[free5GRAN::BCH_PAYLOAD_SIZE + i];
  }
  // Re-compute the bch_payload CRC
  free5GRAN::phy::transport_channel::compute_crc(
      bch_payload, free5GRAN::G_CRC_24_C, bch_crc_recomputed, 32, 25);

  // XOR recomputed CRC with received CRC to determine CRC masq
  for (int i = 0; i < free5GRAN::BCH_CRC_LENGTH; i++) {
    crc_masq[i] = bch_crc[i] ^ bch_crc_recomputed[i];
  }

  /*
   * PBCH payload recovering (TS38.212 7.1.1)
   */
  int A = free5GRAN::BCH_PAYLOAD_SIZE;
  int A_bar = free5GRAN::BCH_PAYLOAD_SIZE - 8;
  int M = A - 3;
  int s_sequence[A], bch_descrambled[free5GRAN::BCH_PAYLOAD_SIZE];
  int sfn_bits[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
  // Find the correct value of v
  for (int v = 0; v < 4; v++) {
    // Generate de-scrambling sequence
    int c_seq[free5GRAN::BCH_PAYLOAD_SIZE + v * M];
    free5GRAN::utils::sequence_generator::generate_c_sequence(
        pci, free5GRAN::BCH_PAYLOAD_SIZE + v * M, c_seq, 0);
    int j = 0;
    // Generate s sequence
    for (int i = 0; i < A; i++) {
      if (i == 0 || i == 6 || i == 24) {
        s_sequence[i] = 0;
      } else {
        s_sequence[i] = c_seq[j + v * M];
        j++;
      }
    }
    // De-scramble bch_payload to bch_descrambled
    free5GRAN::utils::common_utils::scramble(bch_payload, s_sequence,
                                             bch_descrambled,
                                             free5GRAN::BCH_PAYLOAD_SIZE, 0);

    // BCH payload de-interleaving
    int j_sfn = 0;
    int j_hrf = 10;
    int j_ssb = 11;
    int j_other = 14;
    for (int i = 0; i < 32; i++) {
      if (i == 24 || i == 25 || i == 26 || i == 27 || i == 1 || i == 2 ||
          i == 3 || i == 4 || i == 5 || i == 6) {
        mib_bits[i] =
            bch_descrambled[free5GRAN::PBCH_PAYLOAD_INTERLEAVER[j_sfn]];
        j_sfn++;
      } else if (i == 28) {
        mib_bits[i] =
            bch_descrambled[free5GRAN::PBCH_PAYLOAD_INTERLEAVER[j_hrf]];
      } else if (i >= A_bar + 5 && i <= A_bar + 7) {
        mib_bits[i] =
            bch_descrambled[free5GRAN::PBCH_PAYLOAD_INTERLEAVER[j_ssb]];
        j_ssb++;
      } else {
        mib_bits[i] =
            bch_descrambled[free5GRAN::PBCH_PAYLOAD_INTERLEAVER[j_other]];
        j_other++;
      }
    }
    // If final bits correspond to 3rd and 2nd LSB of SFN, correct v was found
    if (sfn_bits[v][0] == mib_bits[25] && sfn_bits[v][1] == mib_bits[26]) {
      break;
    }
  }
}

void free5GRAN::phy::transport_channel::decode_dci(
    int* dci_bits,
    int E,
    int K,
    int* rnti,
    bool& validated,
    vector<int>& decoded_dci_bits) {
  /**
   * \fn decode_dci
   * \brief DCI decoding
   * \standard TS 38.212 V15.2.0 Section 7.3
   *
   * \partial_imp Only DCI Format 1_0 has been tested
   * \details
   * Details:
   * - Rate recovering
   * - Polar decoding
   * - RNTI scrambling
   * - CRC validation
   *
   * \param[in] dci_bits: Input bits sequence
   * \param[in] E: PDCCH payload size
   * \param[in] K: DCI payload size (including CRC)
   * \param[in] rnti: RNTI for identifying DCI Format
   * \param[out] validated: Indicator for CRC validation
   * \param[out] decoded_dci_bits: Output bits sequence
   */
  int n = compute_N_polar_code(E, K, 9);
  int N = pow(2, n);

  BOOST_LOG_TRIVIAL(trace) << "(n, N) = (" + to_string(n) + ", " +
                                  to_string(N) + ")";
  BOOST_LOG_TRIVIAL(trace) << "E = " + to_string(E);
  BOOST_LOG_TRIVIAL(trace) << "K = " + to_string(K);

  int rate_recovered[N], polar_decoded[K], remainder[25], descrambled[K + 24];

  int A = K - 24;
  /*
   * rate recovering
   */
  rate_recover(dci_bits, rate_recovered, 0, E, N, K);
  /*
   * Polar decoding
   */
  polar_decode(rate_recovered, polar_decoded, N, K, 9, 1, 0, 0, E);
  /*
   * RNTI de-masking and CRC validation
   */
  for (int i = 0; i < 24; i++) {
    descrambled[i] = 1;
  }
  for (int i = 0; i < K; i++) {
    if (i < A + 8) {
      descrambled[i + 24] = polar_decoded[i];
    } else {
      descrambled[i + 24] = (polar_decoded[i] + rnti[i - A - 8]) % 2;
    }
  }
  crc_validate(descrambled, free5GRAN::G_CRC_24_C, remainder, K + 24, 25);
  validated = true;
  for (int i : remainder) {
    if (i == 1) {
      validated = false;
      break;
    }
  }
  BOOST_LOG_TRIVIAL(trace) << "## CRC "
                           << ((validated) ? "validated" : "not validated");

  for (int i = 0; i < A; i++) {
    decoded_dci_bits[i] = polar_decoded[i];
  }
}

auto free5GRAN::phy::transport_channel::decode_dl_sch(
    double* dl_sch_bits,
    int n_re,
    float R,
    int nrb,
    int E,
    bool& validated,
    free5GRAN::dci_1_0_si_rnti dci_1_0_si_rnti) -> vector<int> {
  /**
   * \fn decode_dl_sch
   * \brief DL-SCH decoding
   * \standard TS 38.212 V15.2.0 Section 7.2
   *
   * \partial_imp Implemented for one code block (C=1)
   * \details
   * Details:
   * - Rate recovering
   * - LDPC decoding
   * - CRC validation
   *
   * \param[in] dl_sch_bits: Input soft bits sequence
   * \param[in] n_re: Number of RE per PDSCH RB
   * \param[in] R: Code Rate
   * \param[in] nrb: Number of PDSCH allocated RB
   * \param[in] E: PDSCH output sequence length
   * \param[out] validated: CRC validation indicator
   * \param[in] dci_1_0_si_rnti: Input DCI Format 1_0 object
   */

  /*
   * Compute code block segmentation information
   */
  int graph, A, N, K, Zc, i_ls, L_cb, C, B, L, K_p;
  compute_transport_block_size(n_re, R, 2, 1, nrb, A);
  compute_ldpc_base_graph(A, R, graph);
  L = (A > 3824) ? 24 : 16;
  B = A + L;
  compute_code_block_segmentation_info_ldpc(graph, B, Zc, K, i_ls, L_cb, C, N,
                                            K_p);

  BOOST_LOG_TRIVIAL(trace) << "(TBS, graph) = " << A << ", " << graph;
  BOOST_LOG_TRIVIAL(trace) << "B = " << B;
  BOOST_LOG_TRIVIAL(trace) << "Zc = " << Zc;
  BOOST_LOG_TRIVIAL(trace) << "K = " << K;
  BOOST_LOG_TRIVIAL(trace) << "i_ls = " << i_ls;
  BOOST_LOG_TRIVIAL(trace) << "L = " << L;
  BOOST_LOG_TRIVIAL(trace) << "C = " << C;
  BOOST_LOG_TRIVIAL(trace) << "N = " << N;
  BOOST_LOG_TRIVIAL(trace) << "L_cb = " << L_cb;
  BOOST_LOG_TRIVIAL(trace) << "K_p = " << K_p;
  BOOST_LOG_TRIVIAL(trace) << "E = " << E;

  /*
   * Rate recovering
   */
  auto* rate_recovered = new double[N];
  rate_recover_ldpc(dl_sch_bits, N, 1, E, dci_1_0_si_rnti.rv, 2, C, Zc, graph,
                    K, K_p, rate_recovered);

  /*
   * LDPC decoding
   */
  int ldpc_decoded[K];
  auto start = chrono::steady_clock::now();
  ldpc_decode(rate_recovered, N, Zc, graph, K, i_ls, ldpc_decoded);
  auto end = chrono::steady_clock::now();
  auto diff = end - start;
  BOOST_LOG_TRIVIAL(trace) << "## LDPC execution time "
                           << chrono::duration<double, milli>(diff).count()
                           << "ms";

  int desegmented[B];
  for (int i = 0; i < B; i++) {
    desegmented[i] = ldpc_decoded[i];
  }

  /*
   * CRC validation
   */
  int remainder[L];
  if (L == 24) {
    crc_validate(desegmented, free5GRAN::G_CRC_24_C, remainder, B, L + 1);
  } else {
    crc_validate(desegmented, free5GRAN::G_CRC_16, remainder, B, L + 1);
  }

  validated = true;
  for (int i = 0; i < L + 1; i++) {
    if (remainder[i] == 1) {
      validated = false;
      break;
    }
  }
  vector<int> output_bits(A);

  for (int i = 0; i < A; i++) {
    output_bits[i] = desegmented[i];
  }

  BOOST_LOG_TRIVIAL(trace) << "## CRC "
                           << ((validated) ? "validated" : "not validated");

  return output_bits;
}