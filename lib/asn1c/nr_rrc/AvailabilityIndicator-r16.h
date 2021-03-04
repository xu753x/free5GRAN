/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "NR-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -no-gen-example -pdu=all`
 */

#ifndef	_AvailabilityIndicator_r16_H_
#define	_AvailabilityIndicator_r16_H_


#include "asn_application.h"

/* Including external dependencies */
#include "AI-RNTI-r16.h"
#include "NativeInteger.h"
#include "asn_SEQUENCE_OF.h"
#include "constr_SEQUENCE_OF.h"
#include "AvailabilityCombinationsPerCellIndex-r16.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct AvailabilityCombinationsPerCell_r16;

/* AvailabilityIndicator-r16 */
typedef struct AvailabilityIndicator_r16 {
	AI_RNTI_r16_t	 ai_RNTI_r16;
	long	 dci_PayloadSizeAI_r16;
	struct AvailabilityIndicator_r16__availableCombToAddModList_r16 {
		A_SEQUENCE_OF(struct AvailabilityCombinationsPerCell_r16) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *availableCombToAddModList_r16;
	struct AvailabilityIndicator_r16__availableCombToReleaseList_r16 {
		A_SEQUENCE_OF(AvailabilityCombinationsPerCellIndex_r16_t) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *availableCombToReleaseList_r16;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} AvailabilityIndicator_r16_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_AvailabilityIndicator_r16;
extern asn_SEQUENCE_specifics_t asn_SPC_AvailabilityIndicator_r16_specs_1;
extern asn_TYPE_member_t asn_MBR_AvailabilityIndicator_r16_1[4];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "AvailabilityCombinationsPerCell-r16.h"

#endif	/* _AvailabilityIndicator_r16_H_ */
#include "asn_internal.h"