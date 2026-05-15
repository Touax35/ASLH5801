#!/usr/bin/env python3

import argparse
import csv
import re



def main():


    lh5801_dot_h_file = []
    lh5801pst_dot_c_file = []
    lh5801ope_dot_c_file = []


    #/*
    # * Registers
    # */
    modes = {
            "R_NULL":	    0,	# not found
            "R_XH":		    1,	# XH
            "R_XL":		    2,	# XL
            "R_YH":		    3,	# YH
            "R_YL":		    4,	# YL
            "R_UH":		    5,	# UH
            "R_UL":		    6,	# UL
            "R_VH":		    7,	# VH
            "R_VL":		    8,	# VL
            "R_A":		    9,	# A
            "R_X":		    10,	# X
            "R_Y":		    11,	# Y
            "R_U":		    12,	# U
            "R_V":		    13,	# V
            "R_P":		    14,	# P
            "R_S":		    15,	# S
            "S_IND_X":	    16,	# (X)
            "S_IND_Y":	    17,	# (Y)
            "S_IND_U":	    18,	# (U)
            "S_IND_V":	    19,	# (V)
            # always keep the +4 betwwen (.) and #(.)
            # as +4 is hard coded in lh5801adr.c (function addr())
            # the main reason is that the '#()' can't be read at once
            # so '#' is read first then '()' and + 4 is added to '()' to make '#()'
            "S_IND_ME1_X":	20,	# #(X) : (X) + 4
            "S_IND_ME1_Y":	21,	# #(Y) : (Y) + 4
            "S_IND_ME1_U":	22,	# #(U) : (U) + 4
            "S_IND_ME1_V":	23,	# #(V) : (V) + 4
    #/*
    # * Symbol types
    # */
            "S_IND_IMMED":	    24,    # // (ab)
            "S_IND_ME1_IMMED":	25,    # // #(ab)
            "S_IMMED":		    26,    # // i, ab
            "S_PDISPL":		    27,    # // +i
            "S_NDISPL":		    28,    # // -i
    }

    for key, value in modes.items():
            lh5801_dot_h_file.append(f"#define	{key}	{value}")

    map_modes = {
        "XH":    modes["R_XH"],
        "XL":    modes["R_XL"],
        "YH":    modes["R_YH"],
        "YL":    modes["R_YL"],
        "UH":    modes["R_UH"],
        "UL":    modes["R_UL"],
        "VH":    modes["R_VH"],
        "VL":    modes["R_VL"],
        "A":     modes["R_A"],
        "X":     modes["R_X"],
        "Y":     modes["R_Y"],
        "U":     modes["R_U"],
        "V":     modes["R_V"],
        "P":     modes["R_P"],
        "S":     modes["R_S"],
        "(X)":   modes["S_IND_X"],
        "(Y)":   modes["S_IND_Y"],
        "(U)":   modes["S_IND_U"],
        "(V)":   modes["S_IND_V"],
        "#(X)":  modes["S_IND_ME1_X"],
        "#(Y)":  modes["S_IND_ME1_Y"],
        "#(U)":  modes["S_IND_ME1_U"],
        "#(V)":  modes["S_IND_ME1_V"],
        "(ab)":  modes["S_IND_IMMED"],
        "#(ab)": modes["S_IND_ME1_IMMED"],
        "ab":    modes["S_IMMED"], # "ab" and "i" (that is 16 and 8 bits)
        "i":     modes["S_IMMED"], # share the same mode
        "+i":    modes["S_PDISPL"],
        "-i":    modes["S_NDISPL"],
    }

    lh5801v = []
    lh5801 = ["VH", "VL", "V", "(V)", "#(V)"]

    allowed_lh5801 = [0] * len(map_modes)
    allowed_lh5801v = [0] * len(map_modes)
    for key, value in map_modes.items():
        if key in lh5801v:
            allowed_lh5801v[value] = 0
        else:
            allowed_lh5801v[value] = 1
        if key in lh5801:
            allowed_lh5801[value] = 0
        else:
            allowed_lh5801[value] = 1

    lh5801ope_dot_c_file.append("static const int allowed_lh5801[] = {")
    lh5801ope_dot_c_file.append("//nul,XH,XL,YH,YL,UH,UL,VH,VL,A,X,Y,U,V,P,S,(X),(Y),(U),(V),#(X),#(Y),#(U),#(V),(ab),#(ab),i ab,+i,-i")
    lh5801ope_dot_c_file.append(", ".join(map(str, allowed_lh5801)))
    lh5801ope_dot_c_file.append("};")
    lh5801ope_dot_c_file.append("static const int allowed_lh5801v[] = {")
    lh5801ope_dot_c_file.append("//nul,XH,XL,YH,YL,UH,UL,VH,VL,A,X,Y,U,V,P,S,(X),(Y),(U),(V),#(X),#(Y),#(U),#(V),(ab),#(ab),i ab,+i,-i")
    lh5801ope_dot_c_file.append(", ".join(map(str, allowed_lh5801v)))
    lh5801ope_dot_c_file.append("};")

    lh5801pst_dot_c_file.append("")
    lh5801pst_dot_c_file.append("	/* Machines */")
    lh5801pst_dot_c_file.append("")
    lh5801pst_dot_c_file.append("    {	NULL,	\".lh5801\",		S_CPU,		0,	X_LH5801	},")
    lh5801pst_dot_c_file.append("    {	NULL,	\".lh5801v\",		S_CPU,		0,	X_LH5801V	},")
    lh5801pst_dot_c_file.append("")
    lh5801pst_dot_c_file.append("	/* lh5801 */")
    lh5801pst_dot_c_file.append("")

    # read CSV file
    lines = []
    with open('lh5801v.csv', 'r', encoding='utf-8') as file:
        reader = csv.reader(file)
        for row in reader:
            if row[0] == "MNEMONIC":
                continue
            if row[0] == "INV":
                # remove invalid instructions
                continue
            lines.append(row)

    # sort instructions with and without operand
    instructions_without_operand = []
    instructions_with_operands = []
    instructions_VEJ = []
    for row in lines:
        if row[1] == "":
            instructions_without_operand.append(row)
        elif row[0] == "VEJ" and re.fullmatch(r'[0-9A-F][0-9A-F]', row[1], re.IGNORECASE):
            instructions_VEJ.append(row)
        else:
            instructions_with_operands.append(row)

    # list of mnemonics for instructions without operand
    mnemonics_without_operand = {}
    for row in instructions_without_operand:
        mnemonics_without_operand[row[0]] = 0
    for row in instructions_without_operand:
        mnemonics_without_operand[row[0]] = mnemonics_without_operand[row[0]] + 1

    for key, value in mnemonics_without_operand.items():
        for row in instructions_without_operand:
            row[1] = re.sub(r'^([^ ]*) .*', r'\1', row[1])
            if row[0] == key:
                m = re.fullmatch(r'([^ ]*) *([^ ]*) *.*', row[2], re.IGNORECASE)
                if m:
                    if m.group(1) == "FD":
                        pop = "0xFD"
                        op = f"0x{m.group(2)}"
                    else:
                        pop = "0x00"
                        op = f"0x{m.group(1)}"
        if pop == "0xFD":
            lh5801pst_dot_c_file.append(f"    {{	NULL,	\"{key}\",	S_FD_LESS,	0,	{op}	}},")
        else:
            lh5801pst_dot_c_file.append(f"    {{	NULL,	\"{key}\",	S_LESS, 	0,	{op}	}},")

    lh5801pst_dot_c_file.append(f"    {{	NULL,	\"VEJ\",	S_VEJ,	    0,	0x00	}},")

    # list of mnemonics for instructions with instructions_with_operands
    mnemonics = {}
    for row in instructions_with_operands:
        mnemonics[row[0]] = 0
    for row in instructions_with_operands:
        mnemonics[row[0]] = mnemonics[row[0]] + 1

    #for key, value in {"BCH": 10 }.items(): #mnemonics.items():
    instruction_types = 40
    last_key = list(mnemonics.keys())[-1]
    for key, value in mnemonics.items():
        pop = ["0x00"] * len(map_modes)
        op = ["0x00"] * len(map_modes)
        size = [0] * len(map_modes)
        for row in instructions_with_operands:
            row[1] = re.sub(r'^([^ ]*) .*', r'\1', row[1])
            if row[0] == key:
                m = re.fullmatch(r'([^ ]*) *([^ ]*) *.*', row[2], re.IGNORECASE)
                if m:
                    if m.group(1) == "FD":
                        pop[map_modes[row[1]]] = "0xFD"
                        op[map_modes[row[1]]] = f"0x{m.group(2)}"
                        size[map_modes[row[1]]] = 2
                        if row[1] == "+i":
                            # map also "+i" on "i"
                            pop[map_modes["i"]] = "0xFD"
                            op[map_modes["i"]] = f"0x{m.group(2)}" # op not used, just as a reminder
                            size[map_modes["i"]] = 2
                    else:
                        pop[map_modes[row[1]]] = "0x00"
                        op[map_modes[row[1]]] = f"0x{m.group(1)}"
                        size[map_modes[row[1]]] = 1
                        if row[1] == "+i":
                            # map also "+i" on "i"
                            pop[map_modes["i"]] = "0x00"
                            op[map_modes["i"]] = f"0x{m.group(1)}" # op not used, just as a reminder
                            size[map_modes["i"]] = 1

        lh5801ope_dot_c_file.append(f"static const opecode_t {key}[{len(map_modes)}] = {{")
        for i in range(len(pop)-1):
            lh5801ope_dot_c_file.append(f" {{{pop[i+1]}, {op[i+1]}, {size[i+1]}}},")
        lh5801ope_dot_c_file.append(f"}};")

        lh5801_dot_h_file.append(f"#define	S_{key}	{instruction_types}")
        instruction_types = instruction_types + 1

        if key == last_key:
            lh5801pst_dot_c_file.append(f"    {{	NULL,	\"{key}\",	S_{key},  S_EOL,	0x00	}}")
        else:
            lh5801pst_dot_c_file.append(f"    {{	NULL,	\"{key}\",	S_{key},	    0,	0x00	}},")

    lh5801_dot_h_file.append(f"#define	S_VEJ	{instruction_types}")
    instruction_types = instruction_types + 1
    lh5801_dot_h_file.append(f"#define	S_LESS	{instruction_types}")
    instruction_types = instruction_types + 1
    lh5801_dot_h_file.append(f"#define	S_FD_LESS	{instruction_types}")
    instruction_types = instruction_types + 1


    lh5801_dot_h_file.append(f"")
    lh5801_dot_h_file.append(f"/*")
    lh5801_dot_h_file.append(f" * CPU Type Split")
    lh5801_dot_h_file.append(f" */")
    lh5801_dot_h_file.append(f"#define	S_CPU	{instruction_types}")
    instruction_types = instruction_types + 1
    lh5801_dot_h_file.append(f"")
    lh5801_dot_h_file.append(f"/*")
    lh5801_dot_h_file.append(f" * CPU Type Split")
    lh5801_dot_h_file.append(f" */")
    lh5801_dot_h_file.append(f"#define	X_CPU	{instruction_types}")
    lh5801_dot_h_file.append(f"")


    parser = argparse.ArgumentParser(
        description="Affiche le contenu des différentes listes."
    )

    parser.add_argument(
        "--header",
        action="store_true",
        help="Output data to be inserted in lh5801.c"
    )

    parser.add_argument(
        "--pst",
        action="store_true",
        help="Output data to be inserted in lh5801pst.c"
    )

    parser.add_argument(
        "--ope",
        action="store_true",
        help="Output containt of lh5801ope.c"
    )

    args = parser.parse_args()

    # Si aucun argument n'est fourni, afficher tout
    if not (args.header or args.pst or args.ope):
        args.header = True
        args.pst = True
        args.ope = True

    if args.header:
        for item in lh5801_dot_h_file:
            print(item)

    if args.pst:
        for item in lh5801pst_dot_c_file:
            print(item)

    if args.ope:
        for item in lh5801ope_dot_c_file:
            print(item)


if __name__ == "__main__":
    main()