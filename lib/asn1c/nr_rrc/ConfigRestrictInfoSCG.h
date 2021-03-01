/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-InterNodeDefinitions"
 * 	found in "fixed_grammar.asn"
 * 	`asn1c -gen-PER -fcompound-names -findirect-choice -no-gen-example`
 */

#ifndef	_ConfigRestrictInfoSCG_H_
#define	_ConfigRestrictInfoSCG_H_


#include "asn_application.h"

/* Including external dependencies */
#include "NativeInteger.h"
#include "P-Max.h"
#include "constr_SEQUENCE.h"
#include "ServCellIndex.h"
#include "BandEntryIndex.h"
#include "asn_SEQUENCE_OF.h"
#include "constr_SEQUENCE_OF.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct BandCombinationInfoList;

/* ConfigRestrictInfoSCG */
typedef struct ConfigRestrictInfoSCG {
	struct BandCombinationInfoList	*allowedBC_ListMRDC;	/* OPTIONAL */
	struct ConfigRestrictInfoSCG__powerCoordination_FR1 {
		P_Max_t	*p_maxNR_FR1;	/* OPTIONAL */
		P_Max_t	*p_maxEUTRA;	/* OPTIONAL */
		P_Max_t	*p_maxUE_FR1;	/* OPTIONAL */
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *powerCoordination_FR1;
	struct ConfigRestrictInfoSCG__servCellIndexRangeSCG {
		ServCellIndex_t	 lowBound;
		ServCellIndex_t	 upBound;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *servCellIndexRangeSCG;
	long	*maxMeasFreqsSCG;	/* OPTIONAL */
	long	*maxMeasIdentitiesSCG_NR;	/* OPTIONAL */
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	struct ConfigRestrictInfoSCG__ext1 {
		struct ConfigRestrictInfoSCG__ext1__selectedBandEntriesMN {
			A_SEQUENCE_OF(BandEntryIndex_t) list;
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} *selectedBandEntriesMN;
		long	*pdcch_BlindDetectionSCG;	/* OPTIONAL */
		long	*maxNumberROHC_ContextSessionsSN;	/* OPTIONAL */
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *ext1;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ConfigRestrictInfoSCG_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ConfigRestrictInfoSCG;
extern asn_SEQUENCE_specifics_t asn_SPC_ConfigRestrictInfoSCG_specs_1;
extern asn_TYPE_member_t asn_MBR_ConfigRestrictInfoSCG_1[6];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "BandCombinationInfoList.h"

#endif	/* _ConfigRestrictInfoSCG_H_ */
#include "asn_internal.h"