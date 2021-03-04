/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "NR-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -no-gen-example -pdu=all`
 */

#ifndef	_T312_r16_H_
#define	_T312_r16_H_


#include "asn_application.h"

/* Including external dependencies */
#include "NativeEnumerated.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum T312_r16 {
	T312_r16_ms0	= 0,
	T312_r16_ms50	= 1,
	T312_r16_ms100	= 2,
	T312_r16_ms200	= 3,
	T312_r16_ms300	= 4,
	T312_r16_ms400	= 5,
	T312_r16_ms500	= 6,
	T312_r16_ms1000	= 7
} e_T312_r16;

/* T312-r16 */
typedef long	 T312_r16_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_T312_r16_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_T312_r16;
extern const asn_INTEGER_specifics_t asn_SPC_T312_r16_specs_1;
asn_struct_free_f T312_r16_free;
asn_struct_print_f T312_r16_print;
asn_constr_check_f T312_r16_constraint;
ber_type_decoder_f T312_r16_decode_ber;
der_type_encoder_f T312_r16_encode_der;
xer_type_decoder_f T312_r16_decode_xer;
xer_type_encoder_f T312_r16_encode_xer;
oer_type_decoder_f T312_r16_decode_oer;
oer_type_encoder_f T312_r16_encode_oer;
per_type_decoder_f T312_r16_decode_uper;
per_type_encoder_f T312_r16_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _T312_r16_H_ */
#include "asn_internal.h"