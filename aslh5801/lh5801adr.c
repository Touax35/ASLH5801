/* lh5801adr.c */

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
 * Read an address specifier. Pack the
 * address information into the supplied
 * `expr' structure. Return the mode of
 * the address.
 *
 * This addr(esp) routine performs the following addressing decoding:
 *
 *	address		mode		flag		addr		base
 *	#n		S_IMMED		0		n		NULL
 *	label		s_type		----		s_addr		s_area
 *	[REG]		S_IND+icode	0		0		NULL
 *	[label]		S_INDM		----		s_addr		s_area
 *	offset[REG]	S_IND+icode	----		offset		----
 */
int
addr(struct expr *esp)
{
	int c, c1, indx;
	char *p;

	/* fix order of '<', '>', and '#' */
	p = ip;
	if (((c = getnb()) == '<') || (c == '>')) {
		p = ip-1;
		if (getnb() == '#') {
			*p = *(ip-1);
			*(ip-1) = c;
		}
	}
	ip = p;

	if ((indx = admode(LH_R)) != 0) {
		if (indx) {
	                esp->e_mode = indx;
			esp->e_base.e_ap = NULL;
		}
	} 
	else if ((c = getnb()) == '#') {
		if ((c1 = getnb()) == LFIND) {
			unget(c1);
			if ((indx = admode(LH_R)) != 0) {
				if (indx) {
					// add +4 to index because the '#()' can't be read at once
					// by admode(LH_R) (the '#' is not an autorised char in this case)
					// so '#' is read first then '()' and + 4 is added to '()' to make '#()'
					// also see transcode.py script
					indx = indx + 4;
			                esp->e_mode = indx;
					esp->e_base.e_ap = NULL;
				}
			} 
			else if ((c1 = getnb()) == LFIND) {
				expr(esp, 0);
				esp->e_mode = S_IND_ME1_IMMED;
				if ((c = getnb()) != RTIND)
					xerr('a', "Missing ')'.");
			} 
			else {
				expr(esp, 0);
				esp->e_mode = S_IMMED;
			}
		} 
		else {
			unget(c1);
			expr(esp, 0);
			esp->e_mode = S_IMMED;
		}
	}
	else if (c == '+') {
		expr(esp, 0);
		esp->e_mode = S_PDISPL;
	}
	else if (c == '-') {
		expr(esp, 0);
		esp->e_mode = S_NDISPL;
	}
	else if (c == LFIND) {

		expr(esp, 0);
		esp->e_mode = S_IND_IMMED;
		if ((c = getnb()) != RTIND)
			xerr('a', "Missing ')'.");
	} 
	else {
		unget(c);
		expr(esp, 0);
		esp->e_mode = S_IMMED;
	}
	return (esp->e_mode);
}

int
addr_VEJ(struct expr *esp)
{
	int c, indx;
	char *p;

	/* fix order of '<', '>', and '#' */
	p = ip;
	if (((c = getnb()) == '<') || (c == '>')) {
		p = ip-1;
		if (getnb() == '#') {
			*p = *(ip-1);
			*(ip-1) = c;
		}
	}
	ip = p;

	if ((indx = admode(LH_R)) != 0) {
		xerr('a', "Invalid Addressing Mode.");
	} 
	else if ((c = getnb()) == '#') {
		xerr('a', "Invalid Addressing Mode.");
	}
	else if (c == '+') {
		xerr('a', "Invalid Addressing Mode.");
	}
	else if (c == '-') {
		xerr('a', "Invalid Addressing Mode.");
	}
	else if (c == LFIND) {
		xerr('a', "Invalid Addressing Mode.");
	} 
	else {
		unget(c);
		expr(esp, 0);
		esp->e_mode = S_IMMED;
	}
	return (esp->e_mode);
}

/*
 * When building a table that has variations of a common
 * symbol always start with the most complex symbol first.
 * for example if x, x+, and x++ are in the same table
 * the order should be x++, x+, and then x.  The search
 * order is then most to least complex.
 */

/*
 * When searching symbol tables that contain characters
 * not of type LTR16, eg with '-' or '+', always search
 * the more complex symbol tables first. For example:
 * searching for x+ will match the first part of x++,
 * a false match if the table with x+ is searched
 * before the table with x++.
 */

/*
 * Enter admode() to search a specific addressing mode table
 * for a match. Return the addressing value on a match or
 * zero for no match.
 */
int
admode(struct adsym *sp)
{
	char *ptr;
	int i;
	char *ips;

	ips = ip;
	unget(getnb());

	i = 0;
	while ( *(ptr = &sp[i].a_str[0]) ) {
		if (srch(ptr)) {
			return(sp[i].a_val);
		}
		i++;
	}
	ip = ips;
	return(0);
}

/*
 *      srch --- does string match ?
 */
int
srch(char *str)
{
	char *ptr;
	ptr = ip;

	while (*ptr && *str) {
		if (ccase[*ptr & 0x007F] != ccase[*str & 0x007F])
			break;
		ptr++;
		str++;
	}
	if (ccase[*ptr & 0x007F] == ccase[*str & 0x007F]) {
		ip = ptr;
		return(1);
	}

	if (!*str)
		if (!(ctype[*ptr & 0x007F] & LTR16)) {
			ip = ptr;
			return(1);
		}
	return(0);
}

/*
 * Registers
 */
struct	adsym	LH_R[] = {		
	{	"XH",	R_XH },		// XH
	{	"XL",	R_XL },		// XL
	{	"YH",	R_YH },		// YH
	{	"YL",	R_YL },		// YL
	{	"UH",	R_UH },		// UH
	{	"UL",	R_UL },		// UL
	{	"VH",	R_VH },		// VH
	{	"VL",	R_VL },		// VL
	{	"A",	R_A },		// A
	{	"X",	R_X },		// X
	{	"Y",	R_Y },		// Y
	{	"U",	R_U },		// U
	{	"V",	R_V },		// V
	{	"P",	R_P },		// P
	{	"S",	R_S },		// S
	{	"(X)",	S_IND_X },		// (X)
	{	"(Y)",	S_IND_Y },		// (Y)
	{	"(U)",	S_IND_U },		// (U)
	{	"(V)",	S_IND_V },		// (V)
	{	"#(X)",	S_IND_ME1_X },	// #(X)	
	{	"#(Y)",	S_IND_ME1_Y },	// #(Y)	
	{	"#(U)",	S_IND_ME1_U },	// #(U)	
	{	"#(V)",	S_IND_ME1_V },	// #(V)	
	{	"",	0000 },			// end
};
