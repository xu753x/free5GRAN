/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "NR-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -no-gen-example -pdu=all`
 */

#ifndef	_SL_TrafficPatternInfo_r16_H_
#define	_SL_TrafficPatternInfo_r16_H_


#include "asn_application.h"

/* Including external dependencies */
#include "NativeEnumerated.h"
#include "NativeInteger.h"
#include "BIT_STRING.h"
#include "SL-QoS-FlowIdentity-r16.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum SL_TrafficPatternInfo_r16__trafficPeriodicity_r16 {
	SL_TrafficPatternInfo_r16__trafficPeriodicity_r16_ms20	= 0,
	SL_TrafficPatternInfo_r16__trafficPeriodicity_r16_ms50	= 1,
	SL_TrafficPatternInfo_r16__trafficPeriodicity_r16_ms100	= 2,
	SL_TrafficPatternInfo_r16__trafficPeriodicity_r16_ms200	= 3,
	SL_TrafficPatternInfo_r16__trafficPeriodicity_r16_ms300	= 4,
	SL_TrafficPatternInfo_r16__trafficPeriodicity_r16_ms400	= 5,
	SL_TrafficPatternInfo_r16__trafficPeriodicity_r16_ms500	= 6,
	SL_TrafficPatternInfo_r16__trafficPeriodicity_r16_ms600	= 7,
	SL_TrafficPatternInfo_r16__trafficPeriodicity_r16_ms700	= 8,
	SL_TrafficPatternInfo_r16__trafficPeriodicity_r16_ms800	= 9,
	SL_TrafficPatternInfo_r16__trafficPeriodicity_r16_ms900	= 10,
	SL_TrafficPatternInfo_r16__trafficPeriodicity_r16_ms1000	= 11
} e_SL_TrafficPatternInfo_r16__trafficPeriodicity_r16;

/* SL-TrafficPatternInfo-r16 */
typedef struct SL_TrafficPatternInfo_r16 {
	long	 trafficPeriodicity_r16;
	long	 timingOffset_r16;
	BIT_STRING_t	 messageSize_r16;
	SL_QoS_FlowIdentity_r16_t	 sl_QoS_FlowIdentity_r16;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SL_TrafficPatternInfo_r16_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_trafficPeriodicity_r16_2;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_SL_TrafficPatternInfo_r16;
extern asn_SEQUENCE_specifics_t asn_SPC_SL_TrafficPatternInfo_r16_specs_1;
extern asn_TYPE_member_t asn_MBR_SL_TrafficPatternInfo_r16_1[4];

#ifdef __cplusplus
}
#endif

#endif	/* _SL_TrafficPatternInfo_r16_H_ */
#include "asn_internal.h"