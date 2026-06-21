/* lh5801.h */

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
 * 
 * Ported by Lionel Tchernatinsky
 * from the ASZ80 assembler.
 *
 * lionel at tchernatins dot ky
 */

/*)BUILD
	$(PROGRAM) =	ASLH5801
	$(INCLUDE) = {
		ASXXXX.H
		LH5801.H
	}
	$(FILES) = {
		LH5801MCH.C
		LH5801ADR.C
		LH5801PST.C
		ASMAIN.C
		ASDBG.C
		ASLEX.C
		ASSYM.C
		ASSUBR.C
		ASEXPR.C
		ASDATA.C
		ASLIST.C
		ASOUT.C
	}
	$(STACK) = 3000
*/

/*
 * Indirect Addressing delimeters
 */
#define	LFIND	'('
#define RTIND	')'

/*
 * Registers
 */
#define R_NULL  0
#define R_XH    1
#define R_XL    2
#define R_YH    3
#define R_YL    4
#define R_UH    5
#define R_UL    6
#define R_VH    7
#define R_VL    8
#define R_A     9
#define R_X     10
#define R_Y     11
#define R_U     12
#define R_V     13
#define R_P     14
#define R_S     15
#define S_IND_X 16
#define S_IND_Y 17
#define S_IND_U 18
#define S_IND_V 19
#define S_IND_ME1_X     20
#define S_IND_ME1_Y     21
#define S_IND_ME1_U     22
#define S_IND_ME1_V     23
#define S_IND_IMMED     24
#define S_IND_ME1_IMMED 25
#define S_IMMED 26
#define S_PDISPL        27
#define S_NDISPL        28
#define S_ADC   40
#define S_ADI   41
#define S_ADR   42
#define S_AND   43
#define S_ANI   44
#define S_BCH   45
#define S_BCR   46
#define S_BCS   47
#define S_BHR   48
#define S_BHS   49
#define S_BII   50
#define S_BIT   51
#define S_BVR   52
#define S_BVS   53
#define S_BZR   54
#define S_BZS   55
#define S_CPA   56
#define S_CPI   57
#define S_DCA   58
#define S_DCS   59
#define S_DEC   60
#define S_DRL   61
#define S_DRR   62
#define S_EAI   63
#define S_INC   64
#define S_JMP   65
#define S_LDA   66
#define S_LDE   67
#define S_LDI   68
#define S_LDX   69
#define S_LIN   70
#define S_LOP   71
#define S_ORA   72
#define S_ORI   73
#define S_POP   74
#define S_PSH   75
#define S_SBC   76
#define S_SBI   77
#define S_SDE   78
#define S_SIN   79
#define S_SJP   80
#define S_STA   81
#define S_STX   82
#define S_VCR   83
#define S_VCS   84
#define S_VHR   85
#define S_VHS   86
#define S_VMJ   87
#define S_VVS   88
#define S_VZR   89
#define S_VZS   90
#define S_XOR   91
#define S_VEJ   92
#define S_LESS  93
#define S_FD_LESS       94

/*
 * CPU Type Split
 */
#define S_CPU   95

/*
 * CPU Type Split
 */
#define X_CPU   96

/*
 * Processor Types (S_CPU)
 */
#define	X_LH5801	0
#define	X_LH5801V	1

struct adsym
{
	char	a_str[4];	/* addressing string */
	int	a_val;		/* addressing mode value */
};

extern  struct  adsym	LH_R[];

	/* machine dependent functions */

/* lh5801adr.c */
extern  int	addr(struct expr *esp);
extern  int	addr_VEJ(struct expr *esp);
extern	int	admode(struct adsym *sp);
extern	int	srch(char *str);

/* lh5801mch.c */
extern  int	genop(int pop, int op, struct expr *esp, int f);
extern	void	machine(struct mne *mp);
extern	void	minit(void);

