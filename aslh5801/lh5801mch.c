/* lh5801mch.c */

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
 * 
 * Ported by Lionel Tchernatinsky
 * from the ASZ80 assembler.
 *
 * lionel at tchernatins dot ky
 */

#include "asxxxx.h"
#include "lh5801.h"

char    *cpu    = "Sharp LH5801";
char	*dsft	= "asm";

int	mchtyp;

struct opecode_t {
	int pop;
    int op;
    int size;
};

typedef struct opecode_t opecode_t;

#include "lh5801ope.h"

void check_opecode(int t) {
	switch(mchtyp) {
		case X_LH5801:
			if (!allowed_lh5801[t])
				xerr('o', "Not a LH5801 instruction.");
			break;
		case X_LH5801V:
			if (!allowed_lh5801v[t])
				xerr('o', "Not an LH5801V instruction.");
			break;
		default:
			if (!allowed_lh5801[t])
				xerr('o', "Not a LH5801 instruction.");
			break;
	}
}

void opecode(const opecode_t ope[]) {
        int t1, t2;
	struct expr e1, e2;

	clrexpr(&e1);
	clrexpr(&e2);
	t1 = addr(&e1);
	check_opecode(t1);

	t2 = 0;
	if (more()) {
		comma(0);
		t2 = addr(&e2);
		if (t2 == 0)
			xerr('a', "Invalid Addressing Mode.");
	}
	if (t1 == 0)
		xerr('a', "Invalid Addressing Mode.");
	if (ope[t1-1].size == 0)
		xerr('a', "Invalid Addressing Mode.");
	if (genop(ope[t1-1].pop, ope[t1-1].op, &e1, 1))
		xerr('b', "Invalid Addressing Mode.");
	if ((t1 == S_IND_IMMED) || (t1 == S_IND_ME1_IMMED)) {
		outrw(&e1, 1);
	}
	else if (t1 == S_IMMED) {
		outrb(&e1, 0);
	}
	if (t2 == S_IMMED) {
		outrb(&e2, 0);
	}
}

void branch_opecode(const opecode_t ope[]) {
        int t1;
	struct expr e1;
        int v2;

	clrexpr(&e1);
	t1 = addr(&e1);

	if (t1 == 0)
		xerr('a', "Invalid Addressing Mode.");
	if (ope[t1-1].size == 0)
		xerr('a', "1: Invalid Addressing Mode.");

	if (t1 == S_IMMED) {
                v2 = (int) (e1.e_addr - dot.s_addr - 2);
                if (pass == 2 && ((v2 < -255) || (v2 > 255)))
			xerr('a', "Branching Range Exceeded.");
                if (v2 < 0) {
			t1 = S_NDISPL;
			v2 = -v2;
		}
		else {
			t1 = S_PDISPL;
		}
		if (genop(ope[t1-1].pop, ope[t1-1].op, &e1, 1))
			xerr('b', "2: Invalid Addressing Mode.");
		outab(v2);
	}
	else {
		if (genop(ope[t1-1].pop, ope[t1-1].op, &e1, 1))
			xerr('b', "3: Invalid Addressing Mode.");
		if (t1 == S_PDISPL) {
			outrb(&e1, 0);
		}
		else if (t1 == S_NDISPL) {
			outrb(&e1, 0);
		}
		else {
			xerr('b', "4: Invalid Addressing Mode.");
		}
	}
}

void ldi_opecode(const opecode_t ope[]) {
        int t1, t2;
	struct expr e1, e2;

	clrexpr(&e1);
	clrexpr(&e2);
	t1 = addr(&e1);
	check_opecode(t1);
        if (t1 != R_S) {
                t2 = 0;
	        if (more()) {
	        	comma(0);
	        	t2 = addr(&e2);
	        	if (t2 == 0)
	        		xerr('a', "Invalid Addressing Mode.");
	        }
	        if (t1 == 0)
	        	xerr('a', "Invalid Addressing Mode.");
	        if (ope[t1-1].size == 0)
	        	xerr('a', "Invalid Addressing Mode.");
	        if (genop(ope[t1-1].pop, ope[t1-1].op, &e1, 1))
	        	xerr('b', "Invalid Addressing Mode.");
	        if ((t1 == S_IND_IMMED) || (t1 == S_IND_ME1_IMMED)) {
	        	outrw(&e1, 1);
	        }
	        else if (t1 == S_IMMED) {
	        	outrb(&e1, 0);
	        }
	        if (t2 == S_IMMED) {
	        	outrb(&e2, 0);
	        }
        } else {
                t2 = 0;
	        if (more()) {
	        	comma(0);
	        	t2 = addr(&e2);
	        	if (t2 == 0)
	        		xerr('a', "Invalid Addressing Mode.");
	        }
	        if (t1 == 0)
	        	xerr('a', "Invalid Addressing Mode.");
	        if (ope[t1-1].size == 0)
	        	xerr('a', "Invalid Addressing Mode.");
	        if (genop(ope[t1-1].pop, ope[t1-1].op, &e1, 1))
	        	xerr('b', "Invalid Addressing Mode.");
	        if (t2 == S_IMMED) {
	        	outrw(&e2, 0);
	        } else {
	        	xerr('b', "Invalid Addressing Mode.");
                }
        }



}

/*
 * Opcode Cycle Definitions
 */
#define	OPCY_SDP	((char) (0xFF))
#define	OPCY_ERR	((char) (0xFE))

#define	OPCY_NONE	((char) (0x80))
#define	OPCY_MASK	((char) (0x7F))

#define	OPCY_CPU	((char) (0xFD))

#define	UN	((char) (OPCY_NONE | 0x00))
#define	P2	((char) (OPCY_NONE | 0x01))
#define	P3	((char) (OPCY_NONE | 0x02))
#define	P4	((char) (OPCY_NONE | 0x03))
#define	P5	((char) (OPCY_NONE | 0x04))
#define	P6	((char) (OPCY_NONE | 0x05))
#define	P7	((char) (OPCY_NONE | 0x06))

/*
 * LH5801 Opcode Cycle Pages
 */

static char  lh5801pg1[256] = {
/*--*--* 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F */
/*--*--* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */
/*00*/   4,10, 7, 6, 4, 4, 7, 4, 4,11, 7, 6, 4, 4, 7, 4,
/*10*/  13,10, 7, 6, 4, 4, 7, 4,12,11, 7, 6, 4, 4, 7, 4,
/*20*/  12,10,16, 6, 4, 4, 7, 4,12,11,16, 6, 4, 4, 7, 4,
/*30*/  12,10,13, 6,11,11,10, 4,12,11,13, 6, 4, 4, 7, 4,
/*40*/   4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
/*50*/   4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
/*60*/   4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
/*70*/   7, 7, 7, 7, 7, 7, 4, 7, 4, 4, 4, 4, 4, 4, 7, 4,
/*80*/   4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
/*90*/   4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
/*A0*/   4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
/*B0*/   4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
/*C0*/  11,10,10,10,17,11, 7,11,11,10,10,P2,17,17, 7,11,
/*D0*/  11,10,10,11,17,11, 7,11,11, 4,10,11,17,P3, 7,11,
/*E0*/  11,10,10,19,17,11, 7,11,11, 4,10, 4,17,P4, 7,11,
/*F0*/  11,10,10, 4,17,11, 7,11,11, 6,10, 4,17,P5, 7,11
};

static char  lh5801pg2[256] = {  /* P2 == CB */
/*--*--* 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F */
/*--*--* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */
/*00*/   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8,
/*10*/   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8,
/*20*/   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8,
/*30*/   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8,
/*40*/   8, 8, 8, 8, 8, 8,12, 8, 8, 8, 8, 8, 8, 8,12, 8,
/*50*/   8, 8, 8, 8, 8, 8,12, 8, 8, 8, 8, 8, 8, 8,12, 8,
/*60*/   8, 8, 8, 8, 8, 8,12, 8, 8, 8, 8, 8, 8, 8,12, 8,
/*70*/   8, 8, 8, 8, 8, 8,12, 8, 8, 8, 8, 8, 8, 8,12, 8,
/*80*/   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8,
/*90*/   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8,
/*A0*/   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8,
/*B0*/   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8,
/*C0*/   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8,
/*D0*/   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8,
/*E0*/   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8,
/*F0*/   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8
};

static char  lh5801pg3[256] = {  /* P3 == DD */
/*--*--* 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F */
/*--*--* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */
/*00*/  UN,UN,UN,UN,UN,UN,UN,UN,UN,15,UN,UN,UN,UN,UN,UN,
/*10*/  UN,UN,UN,UN,UN,UN,UN,UN,UN,15,UN,UN,UN,UN,UN,UN,
/*20*/  UN,14,20,10, 8, 8,11,UN,UN,15,20,10, 8,8 ,11,UN,
/*30*/  UN,UN,UN,UN,23,23,19,UN,UN,15,UN,UN,UN,UN,UN,UN,
/*40*/  UN,UN,UN,UN, 8, 8,19,UN,UN,UN,UN,UN, 8, 8,19,UN,
/*50*/  UN,UN,UN,UN, 8, 8,19,UN,UN,UN,UN,UN, 8, 8,19,UN,
/*60*/   8, 8, 8, 8, 8, 8,19, 8, 8, 8, 8, 8, 8, 8,19, 8,
/*70*/  19,19,19,19,19,19,UN,19,UN,UN,UN,UN, 8, 8,19,UN,
/*80*/  UN,UN,UN,UN, 8, 8,19,UN,UN,UN,UN,UN, 8, 8,19,UN,
/*90*/  UN,UN,UN,UN, 8, 8,19,UN,UN,UN,UN,UN, 8, 8,19,UN,
/*A0*/  UN,UN,UN,UN, 8, 8,19,UN,UN,UN,UN,UN, 8, 8,19,UN,
/*B0*/  UN,UN,UN,UN, 8, 8,19,UN,UN,UN,UN,UN, 8, 8,19,UN,
/*C0*/  UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,P6,UN,UN,UN,UN,
/*D0*/  UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,
/*E0*/  UN,14,UN,23,UN,15,UN,UN,UN, 8,UN,UN,UN,UN,UN,UN,
/*F0*/  UN,UN,UN,UN,UN,UN,UN,UN,UN,10,UN,UN,UN,UN,UN,UN
};

static char  lh5801pg4[256] = {  /* P4 == ED */
/*--*--* 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F */
/*--*--* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */
/*00*/  UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,
/*10*/  UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,
/*20*/  UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,
/*30*/  UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,
+/*40*/  12,12,15,20, 8,14, 8, 9,12,12,15,20, 8,14, 8, 9,
+/*50*/  12,12,15,20, 8,14, 8, 9,12,12,15,20, 8,14, 8, 9,
+/*60*/  12,12,15,20, 8,14, 8,18,12,12,15,20, 8,14, 8,18,
+/*70*/  12,12,15,20, 8,14, 8,UN,12,12,15,20, 8,14, 8,UN,
/*80*/  UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,
/*90*/  UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,
/*A0*/  16,16,16,16,UN,UN,UN,UN,16,16,16,16,UN,UN,UN,UN,
/*B0*/  21,21,21,21,UN,UN,UN,UN,21,21,21,21,UN,UN,UN,UN,
/*C0*/  UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,
/*D0*/  UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,
/*E0*/  UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,
/*F0*/  UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN
};

static char  lh5801pg5[256] = {  /* P5 == FD */
/*--*--* 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F */
/*--*--* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */
/*00*/  UN,UN,UN,UN,UN,UN,UN,UN,UN,15,UN,UN,UN,UN,UN,UN,
/*10*/  UN,UN,UN,UN,UN,UN,UN,UN,UN,15,UN,UN,UN,UN,UN,UN,
/*20*/  UN,14,20,10, 8, 8,11,UN,UN,15,20,10, 8,8 ,11,UN,
/*30*/  UN,UN,UN,UN,23,23,19,UN,UN,15,UN,UN,UN,UN,UN,UN,
/*40*/  UN,UN,UN,UN, 8, 8,19,UN,UN,UN,UN,UN, 8, 8,19,UN,
/*50*/  UN,UN,UN,UN, 8, 8,19,UN,UN,UN,UN,UN, 8, 8,19,UN,
/*60*/   8, 8, 8, 8, 8, 8,19, 8, 8, 8, 8, 8, 8, 8,19, 8,
/*70*/  19,19,19,19,19,19,UN,19,UN,UN,UN,UN, 8, 8,19,UN,
/*80*/  UN,UN,UN,UN, 8, 8,19,UN,UN,UN,UN,UN, 8, 8,19,UN,
/*90*/  UN,UN,UN,UN, 8, 8,19,UN,UN,UN,UN,UN, 8, 8,19,UN,
/*A0*/  UN,UN,UN,UN, 8, 8,19,UN,UN,UN,UN,UN, 8, 8,19,UN,
/*B0*/  UN,UN,UN,UN, 8, 8,19,UN,UN,UN,UN,UN, 8, 8,19,UN,
/*C0*/  UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,P6,UN,UN,UN,UN,
/*D0*/  UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,
/*E0*/  UN,14,UN,23,UN,15,UN,UN,UN, 8,UN,UN,UN,UN,UN,UN,
/*F0*/  UN,UN,UN,UN,UN,UN,UN,UN,UN,10,UN,UN,UN,UN,UN,UN
};

static char  lh5801pg6[256] = {  /* P6 == DD CB */
/*--*--* 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F */
/*--*--* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */
/*00*/  UN,UN,UN,UN,UN,UN,23,UN,UN,UN,UN,UN,UN,UN,23,UN,
/*10*/  UN,UN,UN,UN,UN,UN,23,UN,UN,UN,UN,UN,UN,UN,23,UN,
/*20*/  UN,UN,UN,UN,UN,UN,23,UN,UN,UN,UN,UN,UN,UN,23,UN,
/*30*/  UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,23,UN,
/*40*/  UN,UN,UN,UN,UN,UN,20,UN,UN,UN,UN,UN,UN,UN,20,UN,
/*50*/  UN,UN,UN,UN,UN,UN,20,UN,UN,UN,UN,UN,UN,UN,20,UN,
/*60*/  UN,UN,UN,UN,UN,UN,20,UN,UN,UN,UN,UN,UN,UN,20,UN,
/*70*/  UN,UN,UN,UN,UN,UN,20,UN,UN,UN,UN,UN,UN,UN,20,UN,
/*80*/  UN,UN,UN,UN,UN,UN,23,UN,UN,UN,UN,UN,UN,UN,23,UN,
/*90*/  UN,UN,UN,UN,UN,UN,23,UN,UN,UN,UN,UN,UN,UN,23,UN,
/*A0*/  UN,UN,UN,UN,UN,UN,23,UN,UN,UN,UN,UN,UN,UN,23,UN,
/*B0*/  UN,UN,UN,UN,UN,UN,23,UN,UN,UN,UN,UN,UN,UN,23,UN,
/*C0*/  UN,UN,UN,UN,UN,UN,23,UN,UN,UN,UN,UN,UN,UN,23,UN,
/*D0*/  UN,UN,UN,UN,UN,UN,23,UN,UN,UN,UN,UN,UN,UN,23,UN,
/*E0*/  UN,UN,UN,UN,UN,UN,23,UN,UN,UN,UN,UN,UN,UN,23,UN,
/*F0*/  UN,UN,UN,UN,UN,UN,23,UN,UN,UN,UN,UN,UN,UN,23,UN
};

static char  lh5801pg7[256] = {  /* P7 == FD CB */
/*--*--* 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F */
/*--*--* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */
/*00*/  UN,UN,UN,UN,UN,UN,23,UN,UN,UN,UN,UN,UN,UN,23,UN,
/*10*/  UN,UN,UN,UN,UN,UN,23,UN,UN,UN,UN,UN,UN,UN,23,UN,
/*20*/  UN,UN,UN,UN,UN,UN,23,UN,UN,UN,UN,UN,UN,UN,23,UN,
/*30*/  UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,UN,23,UN,
/*40*/  UN,UN,UN,UN,UN,UN,20,UN,UN,UN,UN,UN,UN,UN,20,UN,
/*50*/  UN,UN,UN,UN,UN,UN,20,UN,UN,UN,UN,UN,UN,UN,20,UN,
/*60*/  UN,UN,UN,UN,UN,UN,20,UN,UN,UN,UN,UN,UN,UN,20,UN,
/*70*/  UN,UN,UN,UN,UN,UN,20,UN,UN,UN,UN,UN,UN,UN,20,UN,
/*80*/  UN,UN,UN,UN,UN,UN,23,UN,UN,UN,UN,UN,UN,UN,23,UN,
/*90*/  UN,UN,UN,UN,UN,UN,23,UN,UN,UN,UN,UN,UN,UN,23,UN,
/*A0*/  UN,UN,UN,UN,UN,UN,23,UN,UN,UN,UN,UN,UN,UN,23,UN,
/*B0*/  UN,UN,UN,UN,UN,UN,23,UN,UN,UN,UN,UN,UN,UN,23,UN,
/*C0*/  UN,UN,UN,UN,UN,UN,23,UN,UN,UN,UN,UN,UN,UN,23,UN,
/*D0*/  UN,UN,UN,UN,UN,UN,23,UN,UN,UN,UN,UN,UN,UN,23,UN,
/*E0*/  UN,UN,UN,UN,UN,UN,23,UN,UN,UN,UN,UN,UN,UN,23,UN,
/*F0*/  UN,UN,UN,UN,UN,UN,23,UN,UN,UN,UN,UN,UN,UN,23,UN
};

static char *lh5801Page[7] = {
    lh5801pg1, lh5801pg2, lh5801pg3, lh5801pg4,
    lh5801pg5, lh5801pg6, lh5801pg7
};


/*
 * Process a machine op.
 */
void
machine(struct mne *mp)
{
	int op, t1;
	struct expr e1, e2;
	int rf;

	/*
	 * Using Internal Format
	 * For Cycle Counting
	 */
	opcycles = OPCY_NONE;

	clrexpr(&e1);
	clrexpr(&e2);
	op = (int) mp->m_valu;
	rf = mp->m_type;

	switch (rf) {
        case S_ADC:
                opecode(ADC);
                break;
        case S_ADI:
                opecode(ADI);
                break;
        case S_ADR:
                opecode(ADR);
                break;
        case S_AND:
                opecode(AND);
                break;
        case S_ANI:
                opecode(ANI);
                break;
        case S_BCH:
                branch_opecode(BCH);
                break;
        case S_BCR:
                branch_opecode(BCR);
                break;
        case S_BCS:
                branch_opecode(BCS);
                break;
        case S_BHR:
                branch_opecode(BHR);
                break;
        case S_BHS:
                branch_opecode(BHS);
                break;
        case S_BII:
                opecode(BII);
                break;
        case S_BIT:
                opecode(BIT);
                break;
        case S_BVR:
                branch_opecode(BVR);
                break;
        case S_BVS:
                branch_opecode(BVS);
                break;
        case S_BZR:
                branch_opecode(BZR);
                break;
        case S_BZS:
                branch_opecode(BZS);
                break;
        case S_CPA:
                opecode(CPA);
                break;
        case S_CPI:
                opecode(CPI);
                break;
        case S_DCA:
                opecode(DCA);
                break;
        case S_DCS:
                opecode(DCS);
                break;
        case S_DEC:
                opecode(DEC);
                break;
        case S_DRL:
                opecode(DRL);
                break;
        case S_DRR:
                opecode(DRR);
                break;
        case S_EAI:
                opecode(EAI);
                break;
        case S_INC:
                opecode(INC);
                break;
        case S_SJP:
	case S_JMP:
		clrexpr(&e1);
		t1 = addr(&e1);
		if (t1 == S_IMMED) {
                        if (rf == S_SJP) {
			        outab(SJP[t1-1].op);
                        } else {
			        outab(JMP[t1-1].op);
                        }
			outrw(&e1, 1);
		} else {
			xerr('b', "Invalid Addressing Mode.");
		}
		break;
        case S_LDA:
                opecode(LDA);
                break;
        case S_LDE:
                opecode(LDE);
                break;
        case S_LDI:
                ldi_opecode(LDI);
                break;
        case S_LDX:
                opecode(LDX);
                break;
        case S_LIN:
                opecode(LIN);
                break;
        case S_LOP:
                opecode(LOP);
                break;
        case S_ORA:
                opecode(ORA);
                break;
        case S_ORI:
                opecode(ORI);
                break;
        case S_POP:
                opecode(POP);
                break;
        case S_PSH:
                opecode(PSH);
                break;
        case S_SBC:
                opecode(SBC);
                break;
        case S_SBI:
                opecode(SBI);
                break;
        case S_SDE:
                opecode(SDE);
                break;
        case S_SIN:
                opecode(SIN);
                break;
        case S_STA:
                opecode(STA);
                break;
        case S_STX:
                opecode(STX);
                break;
        case S_VCR:
                opecode(VCR);
                break;
        case S_VCS:
                opecode(VCS);
                break;
        case S_VHR:
                opecode(VHR);
                break;
        case S_VHS:
                opecode(VHS);
                break;
        case S_VMJ:
                opecode(VMJ);
                break;
        case S_VVS:
                opecode(VVS);
                break;
        case S_VZR:
                opecode(VZR);
                break;
        case S_VZS:
                opecode(VZS);
                break;
        case S_XOR:
                opecode(XOR);
                break;
	case S_VEJ:
		clrexpr(&e1);
		t1 = addr_VEJ(&e1);

		if (t1 == S_IMMED) {
			outrb(&e1, 1);
		} else {
			xerr('b', "Invalid Addressing Mode.");
		}
		break;
	case S_LESS:
		outab(op);
		break;
	case S_FD_LESS:
		outab(0xFD);
		outab(op);
		break;

	case S_CPU:
		opcycles = OPCY_CPU;
		mchtyp = op;
		sym[2].s_addr = op;
		lmode = SLIST;
		break;

	default:
		opcycles = OPCY_ERR;
		xerr('o', "Internal Opcode Error.");
		break;
	}

	if (rf != S_CPU) {
		if (mchtyp == X_LH5801) {
			if (rf > S_CPU)
				xerr('o', "Not a LH5801 instruction.");
		}
//		} else
//		if (mchtyp == X_HD64) {
//			if ((rf > S_CPU) && (rf < X_CPU))
//				xerr('o', "Not an HD64180 instruction.");
//		} else
//		if (mchtyp == X_8080) {
//			if ((i80pg1[cb[0] & 0xFF]) == UN)
//				xerr('o', "Not an 8080 instruction.");
//			if (rf > S_CPU)
//				xerr('o', "Not an 8080 instruction.");
//		} else
//		if (mchtyp == X_8085) {
//			if ((i85pg1[cb[0] & 0xFF]) == UN)
//				xerr('o', "Not a standard 8085 instruction.");
//			if (rf > X_CPU)
//				xerr('o', "Not a standard 8085 instruction.");
//		} else
//		if (mchtyp == X_8085X) {
//			if (rf > X_CPU)
//				xerr('o', "Not an 8085 instruction.");
//		}
	}

	if (opcycles == OPCY_NONE) {
		switch(mchtyp) {
		default:
		case X_LH5801:
			opcycles = lh5801pg1[cb[0] & 0xFF];
			while ((opcycles & OPCY_NONE) && (opcycles & OPCY_MASK)) {
				switch (opcycles) {
				case P2:	/* CB xx	*/
				case P3:	/* DD xx	*/
				case P4:	/* ED xx	*/
				case P5:	/* FD xx	*/
					opcycles = lh5801Page[opcycles & OPCY_MASK][cb[1] & 0xFF];
					break;
				case P6:	/* DD CB -- xx	*/
				case P7:	/* FD CB -- xx	*/
					opcycles = lh5801Page[opcycles & OPCY_MASK][cb[3] & 0xFF];
					break;
				default:
					opcycles = OPCY_NONE;
					break;
				}
			}
			break;

//		case X_ZXN:
//			opcycles = zxnPage[0][cb[0] & 0xFF];
//			while ((opcycles & OPCY_NONE) && (opcycles & OPCY_MASK)) {
//			switch (opcycles) {
//				case P2:	/* CB xx	*/
//				case P3:	/* DD xx	*/
//				case P4:	/* ED xx	*/
//				case P5:	/* FD xx	*/
//					opcycles = zxnPage[opcycles & OPCY_MASK][cb[1] & 0xFF];
//					break;
//				case P6:	/* DD CB -- xx	*/
//				case P7:	/* FD CB -- xx	*/
//					opcycles = zxnPage[opcycles & OPCY_MASK][cb[3] & 0xFF];
//					break;
//				default:
//					opcycles = OPCY_NONE;
//					break;
//				}
//			}
//			break;
//
//		case X_HD64:
//			opcycles = hd64pg1[cb[0] & 0xFF];
//			while ((opcycles & OPCY_NONE) && (opcycles & OPCY_MASK)) {
//				switch (opcycles) {
//				case P2:	/* CB xx	*/
//				case P3:	/* DD xx	*/
//				case P4:	/* ED xx	*/
//				case P5:	/* FD xx	*/
//					opcycles = hd64Page[opcycles & OPCY_MASK][cb[1] & 0xFF];
//					break;
//				case P6:	/* DD CB -- xx	*/
//				case P7:	/* FD CB -- xx	*/
//					opcycles = hd64Page[opcycles & OPCY_MASK][cb[3] & 0xFF];
//					break;
//				default:
//					opcycles = OPCY_NONE;
//					break;
//				}
//			}
//			break;
//
//		case X_8080:
//			opcycles = i80pg1[cb[0] & 0xFF];
//			break;
//
//		case X_8085:
//			opcycles = i85pg1[cb[0] & 0xFF];
//			break;
//
//		case X_8085X:
//			opcycles = x85pg1[cb[0] & 0xFF];
//			break;
		}
	}
//	/*
//	 * Translate To External Format
//	 */
//	if (opcycles == OPCY_NONE) { opcycles  =  CYCL_NONE; } else
//	if (opcycles  & OPCY_NONE) { opcycles |= (CYCL_NONE | 0x3F00); }
}

/*
 * general addressing evaluation
 * return(0) if general addressing mode output, else
 * return(esp->e_mode)
 */
int
genop(int pop, int op, struct expr *esp, int f)
{
	if (pop)
		outab(pop);
	outab(op);
	return(0);
}

/*
 * Machine dependent initialization
 */
void
minit(void)
{
	/*
	 * Byte Order
	 */
	hilo = 1;

	/*
	 * Default Machine Type
	 */
	mchtyp = X_LH5801;
	sym[2].s_addr = X_LH5801;
}

