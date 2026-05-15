/* lh5801pst.c */

/*
 *  Copyright (C) 1989-2025  Alan R. Baldwin
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * Alan R. Baldwin
 * 721 Berkeley St.
 * Kent, Ohio  44240
 */

#include "asxxxx.h"
#include "lh5801.h"

/*
 * Coding Banks
 */
struct	bank	bank[2] = {
    /*	The '_CODE' area/bank has a NULL default file suffix.	*/
    {	NULL,		"_CSEG",	NULL,		0,	0,	0,	0,	0	},
    {	&bank[0],	"_DSEG",	"_DS",		1,	0,	0,	0,	B_FSFX	}
};

/*
 * Coding Areas
 */
struct	area	area[2] = {
    {	NULL,		&bank[0],	"_CODE",	0,	0,	0,	A_1BYTE|A_BNK|A_CSEG	},
    {	&area[0],	&bank[1],	"_DATA",	1,	0,	0,	A_1BYTE|A_BNK|A_DSEG	}
};

/*
 * Basic Relocation Mode Definition
 *
 *	#define		R_NORM	0000		No Bit Positioning
 */
char	mode0[32] = {	/* R_NORM */
	'\200',	'\201',	'\202',	'\203',	'\204',	'\205',	'\206',	'\207',
	'\210',	'\211',	'\212',	'\213',	'\214',	'\215',	'\216',	'\217',
	'\220',	'\221',	'\222',	'\223',	'\224',	'\225',	'\226',	'\227',
	'\230',	'\231',	'\232',	'\233',	'\234',	'\235',	'\236',	'\237'
};

/*
 * Additional Relocation Mode Definitions
 */

/* None Required */

/*
 *     *m_def is a pointer to the bit relocation definition.
 *	m_flag indicates that bit position swapping is required.
 *	m_dbits contains the active bit positions for the output.
 *	m_sbits contains the active bit positions for the input.
 *
 *	struct	mode
 *	{
 *		char *	m_def;		Bit Relocation Definition
 *		a_uint	m_flag;		Bit Swapping Flag
 *		a_uint	m_dbits;	Destination Bit Mask
 *		a_uint	m_sbits;	Source Bit Mask
 *	};
 */
struct	mode	mode[1] = {
    {	&mode0[0],	0,	0x0000FFFF,	0x0000FFFF	}
};

/*
 * Array of Pointers to mode Structures
 */
struct	mode	*modep[16] = {
	&mode[0],	NULL,		NULL,		NULL,
	NULL,		NULL,		NULL,		NULL,
	NULL,		NULL,		NULL,		NULL,
	NULL,		NULL,		NULL,		NULL
};

/*
 * Mnemonic Structure
 */
struct	mne	mne[] = {

	/* assembler */

    {	NULL,	".enabl",	S_OPTN,		0,	O_ENBL	},
    {	NULL,	".dsabl",	S_OPTN,		0,	O_DSBL	},
    {	NULL,	".page",	S_PAGE,		0,	0	},
    {	NULL,	".title",	S_HEADER,	0,	O_TITLE	},
    {	NULL,	".sbttl",	S_HEADER,	0,	O_SBTTL	},
    {	NULL,	".module",	S_MODUL,	0,	0	},
    {	NULL,	".include",	S_INCL,		0,	I_CODE	},
    {	NULL,	".incbin",	S_INCL,		0,	I_BNRY	},
    {	NULL,	".area",	S_AREA,		0,	0	},
    {	NULL,	".psharea",	S_AREA,		0,	O_PSH	},
    {	NULL,	".poparea",	S_AREA,		0,	O_POP	},
    {	NULL,	".bank",	S_BANK,		0,	0	},
    {	NULL,	".org",		S_ORG,		0,	0	},
    {	NULL,	".radix",	S_RADIX,	0,	0	},
    {	NULL,	".globl",	S_GLOBL,	0,	0	},
    {	NULL,	".local",	S_LOCAL,	0,	0	},
    {	NULL,	".if",		S_CONDITIONAL,	0,	O_IF	},
    {	NULL,	".iff",		S_CONDITIONAL,	0,	O_IFF	},
    {	NULL,	".ift",		S_CONDITIONAL,	0,	O_IFT	},
    {	NULL,	".iftf",	S_CONDITIONAL,	0,	O_IFTF	},
    {	NULL,	".ifdef",	S_CONDITIONAL,	0,	O_IFDEF	},
    {	NULL,	".ifndef",	S_CONDITIONAL,	0,	O_IFNDEF},
    {	NULL,	".ifgt",	S_CONDITIONAL,	0,	O_IFGT	},
    {	NULL,	".iflt",	S_CONDITIONAL,	0,	O_IFLT	},
    {	NULL,	".ifge",	S_CONDITIONAL,	0,	O_IFGE	},
    {	NULL,	".ifle",	S_CONDITIONAL,	0,	O_IFLE	},
    {	NULL,	".ifeq",	S_CONDITIONAL,	0,	O_IFEQ	},
    {	NULL,	".ifne",	S_CONDITIONAL,	0,	O_IFNE	},
    {	NULL,	".ifb",		S_CONDITIONAL,	0,	O_IFB	},
    {	NULL,	".ifnb",	S_CONDITIONAL,	0,	O_IFNB	},
    {	NULL,	".ifidn",	S_CONDITIONAL,	0,	O_IFIDN	},
    {	NULL,	".ifdif",	S_CONDITIONAL,	0,	O_IFDIF	},
    {	NULL,	".iif",		S_CONDITIONAL,	0,	O_IIF	},
    {	NULL,	".iiff",	S_CONDITIONAL,	0,	O_IIFF	},
    {	NULL,	".iift",	S_CONDITIONAL,	0,	O_IIFT	},
    {	NULL,	".iiftf",	S_CONDITIONAL,	0,	O_IIFTF	},
    {	NULL,	".iifdef",	S_CONDITIONAL,	0,	O_IIFDEF},
    {	NULL,	".iifndef",	S_CONDITIONAL,	0,	O_IIFNDEF},
    {	NULL,	".iifgt",	S_CONDITIONAL,	0,	O_IIFGT	},
    {	NULL,	".iiflt",	S_CONDITIONAL,	0,	O_IIFLT	},
    {	NULL,	".iifge",	S_CONDITIONAL,	0,	O_IIFGE	},
    {	NULL,	".iifle",	S_CONDITIONAL,	0,	O_IIFLE	},
    {	NULL,	".iifeq",	S_CONDITIONAL,	0,	O_IIFEQ	},
    {	NULL,	".iifne",	S_CONDITIONAL,	0,	O_IIFNE	},
    {	NULL,	".iifb",	S_CONDITIONAL,	0,	O_IIFB	},
    {	NULL,	".iifnb",	S_CONDITIONAL,	0,	O_IIFNB	},
    {	NULL,	".iifidn",	S_CONDITIONAL,	0,	O_IIFIDN},
    {	NULL,	".iifdif",	S_CONDITIONAL,	0,	O_IIFDIF},
    {	NULL,	".else",	S_CONDITIONAL,	0,	O_ELSE	},
    {	NULL,	".endif",	S_CONDITIONAL,	0,	O_ENDIF	},
    {	NULL,	".list",	S_LISTING,	0,	O_LIST	},
    {	NULL,	".nlist",	S_LISTING,	0,	O_NLIST	},
    {	NULL,	".equ",		S_EQU,		0,	O_EQU	},
    {	NULL,	".gblequ",	S_EQU,		0,	O_GBLEQU},
    {	NULL,	".lclequ",	S_EQU,		0,	O_LCLEQU},
    {	NULL,	".byte",	S_DATA,		0,	O_1BYTE	},
    {	NULL,	".db",		S_DATA,		0,	O_1BYTE	},
    {	NULL,	".fcb",		S_DATA,		0,	O_1BYTE	},
    {	NULL,	".word",	S_DATA,		0,	O_2BYTE	},
    {	NULL,	".dw",		S_DATA,		0,	O_2BYTE	},
    {	NULL,	".fdb",		S_DATA,		0,	O_2BYTE	},
/*    {	NULL,	".3byte",	S_DATA,		0,	O_3BYTE	},	*/
/*    {	NULL,	".triple",	S_DATA,		0,	O_3BYTE	},	*/
/*    {	NULL,	".dl",		S_DATA,		0,	O_4BYTE	},	*/
/*    {	NULL,	".4byte",	S_DATA,		0,	O_4BYTE	},	*/
/*    {	NULL,	".quad",	S_DATA,		0,	O_4BYTE	},	*/
/*    {	NULL,	".long",	S_DATA,		0,	O_4BYTE	},	*/
    {	NULL,	".blkb",	S_BLK,		0,	O_1BYTE	},
    {	NULL,	".ds",		S_BLK,		0,	O_1BYTE	},
    {	NULL,	".rmb",		S_BLK,		0,	O_1BYTE	},
    {	NULL,	".rs",		S_BLK,		0,	O_1BYTE	},
    {	NULL,	".blkw",	S_BLK,		0,	O_2BYTE	},
/*    {	NULL,	".blk3",	S_BLK,		0,	O_3BYTE	},	*/
/*    {	NULL,	".blk4",	S_BLK,		0,	O_4BYTE	},	*/
/*    {	NULL,	".blkl",	S_BLK,		0,	O_4BYTE	},	*/
    {	NULL,	".ascii",	S_ASCIX,	0,	O_ASCII	},
    {	NULL,	".ascis",	S_ASCIX,	0,	O_ASCIS	},
    {	NULL,	".asciz",	S_ASCIX,	0,	O_ASCIZ	},
    {	NULL,	".str",		S_ASCIX,	0,	O_ASCII	},
    {	NULL,	".strs",	S_ASCIX,	0,	O_ASCIS	},
    {	NULL,	".strz",	S_ASCIX,	0,	O_ASCIZ	},
    {	NULL,	".fcc",		S_ASCIX,	0,	O_ASCII	},
    {	NULL,	".define",	S_DEFINE,	0,	O_DEF	},
    {	NULL,	".undefine",	S_DEFINE,	0,	O_UNDEF	},
    {	NULL,	".even",	S_BOUNDARY,	0,	O_EVEN	},
    {	NULL,	".odd",		S_BOUNDARY,	0,	O_ODD	},
    {	NULL,	".bndry",	S_BOUNDARY,	0,	O_BNDRY	},
    {	NULL,	".msg"	,	S_MSG,		0,	0	},
    {	NULL,	".assume",	S_ERROR,	0,	O_ASSUME},
    {	NULL,	".error",	S_ERROR,	0,	O_ERROR	},
/*    {	NULL,	".msb",		S_MSB,		0,	0	},	*/
/*    {	NULL,	".lohi",	S_MSB,		0,	O_LOHI	},	*/
/*    {	NULL,	".hilo",	S_MSB,		0,	O_HILO	},	*/
/*    {	NULL,	".8bit",	S_BITS,		0,	O_1BYTE	},	*/
/*    {	NULL,	".16bit",	S_BITS,		0,	O_2BYTE	},	*/
/*    {	NULL,	".24bit",	S_BITS,		0,	O_3BYTE	},	*/
/*    {	NULL,	".32bit",	S_BITS,		0,	O_4BYTE	},	*/
    {	NULL,	".trace",	S_TRACE,	0,	O_TRC	},
    {	NULL,	".ntrace",	S_TRACE,	0,	O_NTRC	},
/*    {	NULL,	"_______",	S_CONST,	0,	VALUE	},	*/
    {	NULL,	".end",		S_END,		0,	0	},
/* sdas specific */
#ifdef ONLY_ASXXXX
    {   NULL,   ".optsdcc",     S_OPTSDCC,      0,      0       },
#endif
/* end sdas specific */

	/* Macro Processor */

    {	NULL,	".macro",	S_MACRO,	0,	O_MACRO	},
    {	NULL,	".endm",	S_MACRO,	0,	O_ENDM	},
    {	NULL,	".mexit",	S_MACRO,	0,	O_MEXIT	},

    {	NULL,	".narg",	S_MACRO,	0,	O_NARG	},
    {	NULL,	".nchr",	S_MACRO,	0,	O_NCHR	},
    {	NULL,	".ntyp",	S_MACRO,	0,	O_NTYP	},

    {	NULL,	".irp",		S_MACRO,	0,	O_IRP	},
    {	NULL,	".irpc",	S_MACRO,	0,	O_IRPC	},
    {	NULL,	".rept",	S_MACRO,	0,	O_REPT	},

    {	NULL,	".nval",	S_MACRO,	0,	O_NVAL	},

    {	NULL,	".mdelete",	S_MACRO,	0,	O_MDEL	},

	/* Machines */

    {	NULL,	".lh5801",		S_CPU,		0,	X_LH5801	},
    {	NULL,	".lh5801v",		S_CPU,		0,	X_LH5801V	},

	/* lh5801 */

    {	NULL,	"AEX",	S_LESS, 	0,	0xF1	},
    {	NULL,	"AM0",	S_FD_LESS,	0,	0xCE	},
    {	NULL,	"AM1",	S_FD_LESS,	0,	0xDE	},
    {	NULL,	"ATP",	S_FD_LESS,	0,	0xCC	},
    {	NULL,	"ATT",	S_FD_LESS,	0,	0xEC	},
    {	NULL,	"CDV",	S_FD_LESS,	0,	0x8E	},
    {	NULL,	"CIN",	S_LESS, 	0,	0xF7	},
    {	NULL,	"HLT",	S_FD_LESS,	0,	0xB1	},
    {	NULL,	"ITA",	S_FD_LESS,	0,	0xBA	},
    {	NULL,	"NOP",	S_LESS, 	0,	0x38	},
    {	NULL,	"OFF",	S_FD_LESS,	0,	0x4C	},
    {	NULL,	"RDP",	S_FD_LESS,	0,	0xC0	},
    {	NULL,	"REC",	S_LESS, 	0,	0xF9	},
    {	NULL,	"RIE",	S_FD_LESS,	0,	0xBE	},
    {	NULL,	"ROL",	S_LESS, 	0,	0xDB	},
    {	NULL,	"ROR",	S_LESS, 	0,	0xD1	},
    {	NULL,	"RPU",	S_LESS, 	0,	0xE3	},
    {	NULL,	"RPV",	S_LESS, 	0,	0xB8	},
    {	NULL,	"RTI",	S_LESS, 	0,	0x8A	},
    {	NULL,	"RTN",	S_LESS, 	0,	0x9A	},
    {	NULL,	"SDP",	S_FD_LESS,	0,	0xC1	},
    {	NULL,	"SEC",	S_LESS, 	0,	0xFB	},
    {	NULL,	"SHL",	S_LESS, 	0,	0xD9	},
    {	NULL,	"SHR",	S_LESS, 	0,	0xD5	},
    {	NULL,	"SIE",	S_FD_LESS,	0,	0x81	},
    {	NULL,	"SPU",	S_LESS, 	0,	0xE1	},
    {	NULL,	"SPV",	S_LESS, 	0,	0xA8	},
    {	NULL,	"TIN",	S_LESS, 	0,	0xF5	},
    {	NULL,	"TTA",	S_FD_LESS,	0,	0xAA	},
    {	NULL,	"VEJ",	S_VEJ,	    0,	0x00	},
    {	NULL,	"ADC",	S_ADC,	    0,	0x00	},
    {	NULL,	"ADI",	S_ADI,	    0,	0x00	},
    {	NULL,	"ADR",	S_ADR,	    0,	0x00	},
    {	NULL,	"AND",	S_AND,	    0,	0x00	},
    {	NULL,	"ANI",	S_ANI,	    0,	0x00	},
    {	NULL,	"BCH",	S_BCH,	    0,	0x00	},
    {	NULL,	"BCR",	S_BCR,	    0,	0x00	},
    {	NULL,	"BCS",	S_BCS,	    0,	0x00	},
    {	NULL,	"BHR",	S_BHR,	    0,	0x00	},
    {	NULL,	"BHS",	S_BHS,	    0,	0x00	},
    {	NULL,	"BII",	S_BII,	    0,	0x00	},
    {	NULL,	"BIT",	S_BIT,	    0,	0x00	},
    {	NULL,	"BVR",	S_BVR,	    0,	0x00	},
    {	NULL,	"BVS",	S_BVS,	    0,	0x00	},
    {	NULL,	"BZR",	S_BZR,	    0,	0x00	},
    {	NULL,	"BZS",	S_BZS,	    0,	0x00	},
    {	NULL,	"CPA",	S_CPA,	    0,	0x00	},
    {	NULL,	"CPI",	S_CPI,	    0,	0x00	},
    {	NULL,	"DCA",	S_DCA,	    0,	0x00	},
    {	NULL,	"DCS",	S_DCS,	    0,	0x00	},
    {	NULL,	"DEC",	S_DEC,	    0,	0x00	},
    {	NULL,	"DRL",	S_DRL,	    0,	0x00	},
    {	NULL,	"DRR",	S_DRR,	    0,	0x00	},
    {	NULL,	"EAI",	S_EAI,	    0,	0x00	},
    {	NULL,	"INC",	S_INC,	    0,	0x00	},
    {	NULL,	"JMP",	S_JMP,	    0,	0x00	},
    {	NULL,	"LDA",	S_LDA,	    0,	0x00	},
    {	NULL,	"LDE",	S_LDE,	    0,	0x00	},
    {	NULL,	"LDI",	S_LDI,	    0,	0x00	},
    {	NULL,	"LDX",	S_LDX,	    0,	0x00	},
    {	NULL,	"LIN",	S_LIN,	    0,	0x00	},
    {	NULL,	"LOP",	S_LOP,	    0,	0x00	},
    {	NULL,	"ORA",	S_ORA,	    0,	0x00	},
    {	NULL,	"ORI",	S_ORI,	    0,	0x00	},
    {	NULL,	"POP",	S_POP,	    0,	0x00	},
    {	NULL,	"PSH",	S_PSH,	    0,	0x00	},
    {	NULL,	"SBC",	S_SBC,	    0,	0x00	},
    {	NULL,	"SBI",	S_SBI,	    0,	0x00	},
    {	NULL,	"SDE",	S_SDE,	    0,	0x00	},
    {	NULL,	"SIN",	S_SIN,	    0,	0x00	},
    {	NULL,	"SJP",	S_SJP,	    0,	0x00	},
    {	NULL,	"STA",	S_STA,	    0,	0x00	},
    {	NULL,	"STX",	S_STX,	    0,	0x00	},
    {	NULL,	"VCR",	S_VCR,	    0,	0x00	},
    {	NULL,	"VCS",	S_VCS,	    0,	0x00	},
    {	NULL,	"VHR",	S_VHR,	    0,	0x00	},
    {	NULL,	"VHS",	S_VHS,	    0,	0x00	},
    {	NULL,	"VMJ",	S_VMJ,	    0,	0x00	},
    {	NULL,	"VVS",	S_VVS,	    0,	0x00	},
    {	NULL,	"VZR",	S_VZR,	    0,	0x00	},
    {	NULL,	"VZS",	S_VZS,	    0,	0x00	},
    {	NULL,	"XOR",	S_XOR,  S_EOL,	0x00	}
};

