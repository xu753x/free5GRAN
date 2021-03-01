/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-InterNodeDefinitions"
 * 	found in "fixed_grammar.asn"
 * 	`asn1c -gen-PER -fcompound-names -findirect-choice -no-gen-example`
 */

#include "CG-Config-v1560-IEs.h"

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static asn_oer_constraints_t asn_OER_type_needForGaps_constr_6 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_needForGaps_constr_6 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 0,  0,  0,  0 }	/* (0..0) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_needForGaps_value2enum_6[] = {
	{ 0,	4,	"true" }
};
static const unsigned int asn_MAP_needForGaps_enum2value_6[] = {
	0	/* true(0) */
};
static const asn_INTEGER_specifics_t asn_SPC_needForGaps_specs_6 = {
	asn_MAP_needForGaps_value2enum_6,	/* "tag" => N; sorted by tag */
	asn_MAP_needForGaps_enum2value_6,	/* N => "tag"; sorted by N */
	1,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_needForGaps_tags_6[] = {
	(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_needForGaps_6 = {
	"needForGaps",
	"needForGaps",
	&asn_OP_NativeEnumerated,
	asn_DEF_needForGaps_tags_6,
	sizeof(asn_DEF_needForGaps_tags_6)
		/sizeof(asn_DEF_needForGaps_tags_6[0]) - 1, /* 1 */
	asn_DEF_needForGaps_tags_6,	/* Same as above */
	sizeof(asn_DEF_needForGaps_tags_6)
		/sizeof(asn_DEF_needForGaps_tags_6[0]), /* 2 */
	{ &asn_OER_type_needForGaps_constr_6, &asn_PER_type_needForGaps_constr_6, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_needForGaps_specs_6	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_requestedCellInfoEUTRA_10[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct CG_Config_v1560_IEs__reportCGI_RequestEUTRA__requestedCellInfoEUTRA, eutraFrequency),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ARFCN_ValueEUTRA,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"eutraFrequency"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CG_Config_v1560_IEs__reportCGI_RequestEUTRA__requestedCellInfoEUTRA, cellForWhichToReportCGI_EUTRA),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_EUTRA_PhysCellId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"cellForWhichToReportCGI-EUTRA"
		},
};
static const ber_tlv_tag_t asn_DEF_requestedCellInfoEUTRA_tags_10[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_requestedCellInfoEUTRA_tag2el_10[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* eutraFrequency */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* cellForWhichToReportCGI-EUTRA */
};
static asn_SEQUENCE_specifics_t asn_SPC_requestedCellInfoEUTRA_specs_10 = {
	sizeof(struct CG_Config_v1560_IEs__reportCGI_RequestEUTRA__requestedCellInfoEUTRA),
	offsetof(struct CG_Config_v1560_IEs__reportCGI_RequestEUTRA__requestedCellInfoEUTRA, _asn_ctx),
	asn_MAP_requestedCellInfoEUTRA_tag2el_10,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_requestedCellInfoEUTRA_10 = {
	"requestedCellInfoEUTRA",
	"requestedCellInfoEUTRA",
	&asn_OP_SEQUENCE,
	asn_DEF_requestedCellInfoEUTRA_tags_10,
	sizeof(asn_DEF_requestedCellInfoEUTRA_tags_10)
		/sizeof(asn_DEF_requestedCellInfoEUTRA_tags_10[0]) - 1, /* 1 */
	asn_DEF_requestedCellInfoEUTRA_tags_10,	/* Same as above */
	sizeof(asn_DEF_requestedCellInfoEUTRA_tags_10)
		/sizeof(asn_DEF_requestedCellInfoEUTRA_tags_10[0]), /* 2 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_requestedCellInfoEUTRA_10,
	2,	/* Elements count */
	&asn_SPC_requestedCellInfoEUTRA_specs_10	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_reportCGI_RequestEUTRA_9[] = {
	{ ATF_POINTER, 1, offsetof(struct CG_Config_v1560_IEs__reportCGI_RequestEUTRA, requestedCellInfoEUTRA),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_requestedCellInfoEUTRA_10,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"requestedCellInfoEUTRA"
		},
};
static const int asn_MAP_reportCGI_RequestEUTRA_oms_9[] = { 0 };
static const ber_tlv_tag_t asn_DEF_reportCGI_RequestEUTRA_tags_9[] = {
	(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_reportCGI_RequestEUTRA_tag2el_9[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* requestedCellInfoEUTRA */
};
static asn_SEQUENCE_specifics_t asn_SPC_reportCGI_RequestEUTRA_specs_9 = {
	sizeof(struct CG_Config_v1560_IEs__reportCGI_RequestEUTRA),
	offsetof(struct CG_Config_v1560_IEs__reportCGI_RequestEUTRA, _asn_ctx),
	asn_MAP_reportCGI_RequestEUTRA_tag2el_9,
	1,	/* Count of tags in the map */
	asn_MAP_reportCGI_RequestEUTRA_oms_9,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_reportCGI_RequestEUTRA_9 = {
	"reportCGI-RequestEUTRA",
	"reportCGI-RequestEUTRA",
	&asn_OP_SEQUENCE,
	asn_DEF_reportCGI_RequestEUTRA_tags_9,
	sizeof(asn_DEF_reportCGI_RequestEUTRA_tags_9)
		/sizeof(asn_DEF_reportCGI_RequestEUTRA_tags_9[0]) - 1, /* 1 */
	asn_DEF_reportCGI_RequestEUTRA_tags_9,	/* Same as above */
	sizeof(asn_DEF_reportCGI_RequestEUTRA_tags_9)
		/sizeof(asn_DEF_reportCGI_RequestEUTRA_tags_9[0]), /* 2 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_reportCGI_RequestEUTRA_9,
	1,	/* Elements count */
	&asn_SPC_reportCGI_RequestEUTRA_specs_9	/* Additional specs */
};

static const ber_tlv_tag_t asn_DEF_nonCriticalExtension_tags_13[] = {
	(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SEQUENCE_specifics_t asn_SPC_nonCriticalExtension_specs_13 = {
	sizeof(struct CG_Config_v1560_IEs__nonCriticalExtension),
	offsetof(struct CG_Config_v1560_IEs__nonCriticalExtension, _asn_ctx),
	0,	/* No top level tags */
	0,	/* No tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_nonCriticalExtension_13 = {
	"nonCriticalExtension",
	"nonCriticalExtension",
	&asn_OP_SEQUENCE,
	asn_DEF_nonCriticalExtension_tags_13,
	sizeof(asn_DEF_nonCriticalExtension_tags_13)
		/sizeof(asn_DEF_nonCriticalExtension_tags_13[0]) - 1, /* 1 */
	asn_DEF_nonCriticalExtension_tags_13,	/* Same as above */
	sizeof(asn_DEF_nonCriticalExtension_tags_13)
		/sizeof(asn_DEF_nonCriticalExtension_tags_13[0]), /* 2 */
	{ 0, 0, SEQUENCE_constraint },
	0, 0,	/* No members */
	&asn_SPC_nonCriticalExtension_specs_13	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_CG_Config_v1560_IEs_1[] = {
	{ ATF_POINTER, 8, offsetof(struct CG_Config_v1560_IEs, pSCellFrequencyEUTRA),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ARFCN_ValueEUTRA,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"pSCellFrequencyEUTRA"
		},
	{ ATF_POINTER, 7, offsetof(struct CG_Config_v1560_IEs, scg_CellGroupConfigEUTRA),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"scg-CellGroupConfigEUTRA"
		},
	{ ATF_POINTER, 6, offsetof(struct CG_Config_v1560_IEs, candidateCellInfoListSN_EUTRA),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"candidateCellInfoListSN-EUTRA"
		},
	{ ATF_POINTER, 5, offsetof(struct CG_Config_v1560_IEs, candidateServingFreqListEUTRA),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CandidateServingFreqListEUTRA,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"candidateServingFreqListEUTRA"
		},
	{ ATF_POINTER, 4, offsetof(struct CG_Config_v1560_IEs, needForGaps),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_needForGaps_6,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"needForGaps"
		},
	{ ATF_POINTER, 3, offsetof(struct CG_Config_v1560_IEs, drx_ConfigSCG),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DRX_Config,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"drx-ConfigSCG"
		},
	{ ATF_POINTER, 2, offsetof(struct CG_Config_v1560_IEs, reportCGI_RequestEUTRA),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		0,
		&asn_DEF_reportCGI_RequestEUTRA_9,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"reportCGI-RequestEUTRA"
		},
	{ ATF_POINTER, 1, offsetof(struct CG_Config_v1560_IEs, nonCriticalExtension),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		0,
		&asn_DEF_nonCriticalExtension_13,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"nonCriticalExtension"
		},
};
static const int asn_MAP_CG_Config_v1560_IEs_oms_1[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
static const ber_tlv_tag_t asn_DEF_CG_Config_v1560_IEs_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_CG_Config_v1560_IEs_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* pSCellFrequencyEUTRA */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* scg-CellGroupConfigEUTRA */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* candidateCellInfoListSN-EUTRA */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* candidateServingFreqListEUTRA */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* needForGaps */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* drx-ConfigSCG */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* reportCGI-RequestEUTRA */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 } /* nonCriticalExtension */
};
asn_SEQUENCE_specifics_t asn_SPC_CG_Config_v1560_IEs_specs_1 = {
	sizeof(struct CG_Config_v1560_IEs),
	offsetof(struct CG_Config_v1560_IEs, _asn_ctx),
	asn_MAP_CG_Config_v1560_IEs_tag2el_1,
	8,	/* Count of tags in the map */
	asn_MAP_CG_Config_v1560_IEs_oms_1,	/* Optional members */
	8, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_CG_Config_v1560_IEs = {
	"CG-Config-v1560-IEs",
	"CG-Config-v1560-IEs",
	&asn_OP_SEQUENCE,
	asn_DEF_CG_Config_v1560_IEs_tags_1,
	sizeof(asn_DEF_CG_Config_v1560_IEs_tags_1)
		/sizeof(asn_DEF_CG_Config_v1560_IEs_tags_1[0]), /* 1 */
	asn_DEF_CG_Config_v1560_IEs_tags_1,	/* Same as above */
	sizeof(asn_DEF_CG_Config_v1560_IEs_tags_1)
		/sizeof(asn_DEF_CG_Config_v1560_IEs_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_CG_Config_v1560_IEs_1,
	8,	/* Elements count */
	&asn_SPC_CG_Config_v1560_IEs_specs_1	/* Additional specs */
};
