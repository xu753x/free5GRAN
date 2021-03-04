/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "NR-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -no-gen-example -pdu=all`
 */

#include "SL-BWP-Generic-r16.h"

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static int
memb_sl_TxDirectCurrentLocation_r16_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 3301)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_type_sl_LengthSymbols_r16_constr_3 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_sl_LengthSymbols_r16_constr_3 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 3,  3,  0,  7 }	/* (0..7) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_sl_StartSymbol_r16_constr_12 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_sl_StartSymbol_r16_constr_12 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 3,  3,  0,  7 }	/* (0..7) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_sl_PSBCH_Config_r16_constr_21 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_sl_PSBCH_Config_r16_constr_21 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_sl_TxDirectCurrentLocation_r16_constr_24 CC_NOTUSED = {
	{ 2, 1 }	/* (0..3301) */,
	-1};
static asn_per_constraints_t asn_PER_memb_sl_TxDirectCurrentLocation_r16_constr_24 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 12,  12,  0,  3301 }	/* (0..3301) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_sl_LengthSymbols_r16_value2enum_3[] = {
	{ 0,	4,	"sym7" },
	{ 1,	4,	"sym8" },
	{ 2,	4,	"sym9" },
	{ 3,	5,	"sym10" },
	{ 4,	5,	"sym11" },
	{ 5,	5,	"sym12" },
	{ 6,	5,	"sym13" },
	{ 7,	5,	"sym14" }
};
static const unsigned int asn_MAP_sl_LengthSymbols_r16_enum2value_3[] = {
	3,	/* sym10(3) */
	4,	/* sym11(4) */
	5,	/* sym12(5) */
	6,	/* sym13(6) */
	7,	/* sym14(7) */
	0,	/* sym7(0) */
	1,	/* sym8(1) */
	2	/* sym9(2) */
};
static const asn_INTEGER_specifics_t asn_SPC_sl_LengthSymbols_r16_specs_3 = {
	asn_MAP_sl_LengthSymbols_r16_value2enum_3,	/* "tag" => N; sorted by tag */
	asn_MAP_sl_LengthSymbols_r16_enum2value_3,	/* N => "tag"; sorted by N */
	8,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_sl_LengthSymbols_r16_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_sl_LengthSymbols_r16_3 = {
	"sl-LengthSymbols-r16",
	"sl-LengthSymbols-r16",
	&asn_OP_NativeEnumerated,
	asn_DEF_sl_LengthSymbols_r16_tags_3,
	sizeof(asn_DEF_sl_LengthSymbols_r16_tags_3)
		/sizeof(asn_DEF_sl_LengthSymbols_r16_tags_3[0]) - 1, /* 1 */
	asn_DEF_sl_LengthSymbols_r16_tags_3,	/* Same as above */
	sizeof(asn_DEF_sl_LengthSymbols_r16_tags_3)
		/sizeof(asn_DEF_sl_LengthSymbols_r16_tags_3[0]), /* 2 */
	{ &asn_OER_type_sl_LengthSymbols_r16_constr_3, &asn_PER_type_sl_LengthSymbols_r16_constr_3, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_sl_LengthSymbols_r16_specs_3	/* Additional specs */
};

static const asn_INTEGER_enum_map_t asn_MAP_sl_StartSymbol_r16_value2enum_12[] = {
	{ 0,	4,	"sym0" },
	{ 1,	4,	"sym1" },
	{ 2,	4,	"sym2" },
	{ 3,	4,	"sym3" },
	{ 4,	4,	"sym4" },
	{ 5,	4,	"sym5" },
	{ 6,	4,	"sym6" },
	{ 7,	4,	"sym7" }
};
static const unsigned int asn_MAP_sl_StartSymbol_r16_enum2value_12[] = {
	0,	/* sym0(0) */
	1,	/* sym1(1) */
	2,	/* sym2(2) */
	3,	/* sym3(3) */
	4,	/* sym4(4) */
	5,	/* sym5(5) */
	6,	/* sym6(6) */
	7	/* sym7(7) */
};
static const asn_INTEGER_specifics_t asn_SPC_sl_StartSymbol_r16_specs_12 = {
	asn_MAP_sl_StartSymbol_r16_value2enum_12,	/* "tag" => N; sorted by tag */
	asn_MAP_sl_StartSymbol_r16_enum2value_12,	/* N => "tag"; sorted by N */
	8,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_sl_StartSymbol_r16_tags_12[] = {
	(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_sl_StartSymbol_r16_12 = {
	"sl-StartSymbol-r16",
	"sl-StartSymbol-r16",
	&asn_OP_NativeEnumerated,
	asn_DEF_sl_StartSymbol_r16_tags_12,
	sizeof(asn_DEF_sl_StartSymbol_r16_tags_12)
		/sizeof(asn_DEF_sl_StartSymbol_r16_tags_12[0]) - 1, /* 1 */
	asn_DEF_sl_StartSymbol_r16_tags_12,	/* Same as above */
	sizeof(asn_DEF_sl_StartSymbol_r16_tags_12)
		/sizeof(asn_DEF_sl_StartSymbol_r16_tags_12[0]), /* 2 */
	{ &asn_OER_type_sl_StartSymbol_r16_constr_12, &asn_PER_type_sl_StartSymbol_r16_constr_12, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_sl_StartSymbol_r16_specs_12	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_sl_PSBCH_Config_r16_21[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SL_BWP_Generic_r16__sl_PSBCH_Config_r16, choice.release),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"release"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SL_BWP_Generic_r16__sl_PSBCH_Config_r16, choice.setup),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_SL_PSBCH_Config_r16,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"setup"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_sl_PSBCH_Config_r16_tag2el_21[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* release */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* setup */
};
static asn_CHOICE_specifics_t asn_SPC_sl_PSBCH_Config_r16_specs_21 = {
	sizeof(struct SL_BWP_Generic_r16__sl_PSBCH_Config_r16),
	offsetof(struct SL_BWP_Generic_r16__sl_PSBCH_Config_r16, _asn_ctx),
	offsetof(struct SL_BWP_Generic_r16__sl_PSBCH_Config_r16, present),
	sizeof(((struct SL_BWP_Generic_r16__sl_PSBCH_Config_r16 *)0)->present),
	asn_MAP_sl_PSBCH_Config_r16_tag2el_21,
	2,	/* Count of tags in the map */
	0, 0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_sl_PSBCH_Config_r16_21 = {
	"sl-PSBCH-Config-r16",
	"sl-PSBCH-Config-r16",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ &asn_OER_type_sl_PSBCH_Config_r16_constr_21, &asn_PER_type_sl_PSBCH_Config_r16_constr_21, CHOICE_constraint },
	asn_MBR_sl_PSBCH_Config_r16_21,
	2,	/* Elements count */
	&asn_SPC_sl_PSBCH_Config_r16_specs_21	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_SL_BWP_Generic_r16_1[] = {
	{ ATF_POINTER, 5, offsetof(struct SL_BWP_Generic_r16, sl_BWP_r16),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BWP,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"sl-BWP-r16"
		},
	{ ATF_POINTER, 4, offsetof(struct SL_BWP_Generic_r16, sl_LengthSymbols_r16),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_sl_LengthSymbols_r16_3,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"sl-LengthSymbols-r16"
		},
	{ ATF_POINTER, 3, offsetof(struct SL_BWP_Generic_r16, sl_StartSymbol_r16),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_sl_StartSymbol_r16_12,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"sl-StartSymbol-r16"
		},
	{ ATF_POINTER, 2, offsetof(struct SL_BWP_Generic_r16, sl_PSBCH_Config_r16),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_sl_PSBCH_Config_r16_21,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"sl-PSBCH-Config-r16"
		},
	{ ATF_POINTER, 1, offsetof(struct SL_BWP_Generic_r16, sl_TxDirectCurrentLocation_r16),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_sl_TxDirectCurrentLocation_r16_constr_24, &asn_PER_memb_sl_TxDirectCurrentLocation_r16_constr_24,  memb_sl_TxDirectCurrentLocation_r16_constraint_1 },
		0, 0, /* No default value */
		"sl-TxDirectCurrentLocation-r16"
		},
};
static const int asn_MAP_SL_BWP_Generic_r16_oms_1[] = { 0, 1, 2, 3, 4 };
static const ber_tlv_tag_t asn_DEF_SL_BWP_Generic_r16_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_SL_BWP_Generic_r16_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* sl-BWP-r16 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* sl-LengthSymbols-r16 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* sl-StartSymbol-r16 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* sl-PSBCH-Config-r16 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 } /* sl-TxDirectCurrentLocation-r16 */
};
asn_SEQUENCE_specifics_t asn_SPC_SL_BWP_Generic_r16_specs_1 = {
	sizeof(struct SL_BWP_Generic_r16),
	offsetof(struct SL_BWP_Generic_r16, _asn_ctx),
	asn_MAP_SL_BWP_Generic_r16_tag2el_1,
	5,	/* Count of tags in the map */
	asn_MAP_SL_BWP_Generic_r16_oms_1,	/* Optional members */
	5, 0,	/* Root/Additions */
	5,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_SL_BWP_Generic_r16 = {
	"SL-BWP-Generic-r16",
	"SL-BWP-Generic-r16",
	&asn_OP_SEQUENCE,
	asn_DEF_SL_BWP_Generic_r16_tags_1,
	sizeof(asn_DEF_SL_BWP_Generic_r16_tags_1)
		/sizeof(asn_DEF_SL_BWP_Generic_r16_tags_1[0]), /* 1 */
	asn_DEF_SL_BWP_Generic_r16_tags_1,	/* Same as above */
	sizeof(asn_DEF_SL_BWP_Generic_r16_tags_1)
		/sizeof(asn_DEF_SL_BWP_Generic_r16_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_SL_BWP_Generic_r16_1,
	5,	/* Elements count */
	&asn_SPC_SL_BWP_Generic_r16_specs_1	/* Additional specs */
};
