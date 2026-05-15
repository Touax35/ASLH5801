        .title Test of LH5801 assembler

	.lh5801v

        n  =        0x20
        nn =        0x0584
        ab =        0x0685
        i  =        0x21

        ;***********************************************************
        ; add with carry to 'A'
        ADC XL               ; 02
        ADC XH               ; 82
        ADC YL               ; 12
        ADC YH               ; 92
        ADC UL               ; 22
        ADC UH               ; A2
        ADC VL               ; 32
        ADC VH               ; B2
        ADC (X)              ; 03
        ADC (Y)              ; 13
        ADC (U)              ; 23
        ADC (V)              ; 33
        ADC# (X)             ; FD 03
        ADC# (Y)             ; FD 13
        ADC# (U)             ; FD 23
        ADC# (V)             ; FD 33
        ADC (nn)             ; A3 05 84
        ADC #(nn)            ; FD A3 05 84
        adc #(nn)            ; FD A3 05 84

        ; notes:
        ;        "ADI A,n" can be replaced by "ADC n".
        ADI A,n              ; B3 20
        ADC n                ; B3 20

        ; add immediate with carry to 'A'
        ADI (X) n            ; 4F 20
        ADI (Y) n            ; 5F 20
        ADI (U) n            ; 6F 20
        ADI (V) n            ; 7F 20
        ADI (nn) n           ; EF 05 84 20
        ADI #(X) n           ; FD 4F 20
        ADI #(Y) n           ; FD 5F 20
        ADI #(U) n           ; FD 6F 20
        ADI #(V) n           ; FD 7F 20
        ADI #(nn) n          ; FD EF 05 84 20

        ADR X                ; FD CA
        ADR Y                ; FD DA
        ADR U                ; FD EA
        ADR V                ; FD FA

        AEX                  ; F1
        AM0                  ; FD CE
        AM1                  ; FD DE

        AND (X)              ; 09
        AND (Y)              ; 19
        AND (U)              ; 29
        AND (V)              ; 39
        AND (ab)             ; A9 06 85
        AND #(X)             ; FD 09
        AND #(Y)             ; FD 19
        AND #(U)             ; FD 29
        AND #(V)             ; FD 39
        AND #(ab)            ; FD A9 06 85

        ; notes:
        ;        "ANI A,n" can be replaced by "AND n".
        AND n                ; B9 20
        ANI A n              ; B9 20

        ANI (X) n            ; 49 20
        ANI (Y) n            ; 59 20
        ANI (U) i            ; 69 21
        ANI (V) i            ; 79 21
        ANI (ab) i           ; E9 06 85 21
        ANI #(X) i           ; FD 49 21
        ANI #(Y) i           ; FD 59 21
        ANI #(U) i           ; FD 69 21
        ANI #(V) i           ; FD 79 21
        ANI #(ab) i          ; FD E9 06 85 21

        ATP                  ; FD CC
        ATT                  ; FD EC

        BCH +i               ; 8E 21
        BCH -i               ; 9E 21
        BCS +i               ; 83 21
        BCS -i               ; 93 21
        BCR +i               ; 81 21
        BCR -i               ; 91 21
        BHS +i               ; 87 21
        BHS -i               ; 97 21
        BHR +i               ; 85 21
        BHR -i               ; 95 21
        BVS +i               ; 8F 21
        BVS -i               ; 9F 21
        BVR +i               ; 8D 21
        BVR -i               ; 9D 21
        BZS +i               ; 8B 21
        BZS -i               ; 9B 21
        BZR +i               ; 89 21
        BZR -i               ; 99 21
tag1:
        BCH tag1             ; 9E 02
        BCH tag2             ; 8E 01
        ADC XL               ; 02
tag2:

        BII (X) i            ; 4D 21
        BII (Y) i            ; 5D 21
        BII (U) i            ; 6D 21
        BII (V) i            ; 7D 21
        BII (ab) i           ; ED 06 85 21
        BII #(X) i           ; FD 4D 21
        BII #(Y) i           ; FD 5D 21
        BII #(U) i           ; FD 6D 21
        BII #(V) i           ; FD 7D 21
        BII #(ab) i          ; FD ED 06 85 21

        BII A i              ; BF 21
        BIT i                ; BF 21

        BIT (X)              ; 0F
        BIT (Y)              ; 1F
        BIT (U)              ; 2F
        BIT (V)              ; 3F
        BIT (ab)             ; AF 06 85
        BIT #(X)             ; FD 0F
        BIT #(Y)             ; FD 1F
        BIT #(U)             ; FD 2F
        BIT #(V)             ; FD 3F
        BIT #(ab)            ; FD AF 06 85

        BVR -i               ; 9D 21
        BVR +i               ; 8D 21
        BVS -i               ; 9F 21
        BVS +i               ; 8F 21
        BZR -i               ; 99 21
        BZR +i               ; 89 21
        BZS -i               ; 9B 21
        BZS +i               ; 8B 21

        CDV                  ; FD 8E
        CIN                  ; F7

        CPA (ab)             ; A7 06 85
        CPA (X)              ; 07
        CPA (Y)              ; 17
        CPA (U)              ; 27
        CPA (V)              ; 37
        CPA #(ab)            ; FD A7 06 85
        CPA #(X)             ; FD 07
        CPA #(Y)             ; FD 17
        CPA #(U)             ; FD 27
        CPA #(V)             ; FD 37
        CPA XH               ; 86
        CPA XL               ; 06
        CPA YH               ; 96
        CPA YL               ; 16
        CPA UH               ; A6
        CPA UL               ; 26
        CPA VH               ; B6
        CPA VL               ; 36

        CPA i                ; B7 21
        CPI A i              ; B7 21

        CPI XH i             ; 4C 21
        CPI XL i             ; 4E 21
        CPI YH i             ; 5C 21
        CPI YL i             ; 5E 21
        CPI UH i             ; 6C 21
        CPI UL i             ; 6E 21
        CPI VH i             ; 7C 21
        CPI VL i             ; 7E 21

        DCA (X)              ; 8C
        DCA (Y)              ; 9C
        DCA (U)              ; AC
        DCA (V)              ; BC
        DCA #(X)             ; FD 8C
        DCA #(Y)             ; FD 9C
        DCA #(U)             ; FD AC
        DCA #(V)             ; FD BC

        DCS (X)              ; 0C
        DCS (Y)              ; 1C
        DCS (U)              ; 2C
        DCS (V)              ; 3C
        DCS #(X)             ; FD 0C
        DCS #(Y)             ; FD 1C
        DCS #(U)             ; FD 2C
        DCS #(V)             ; FD 3C

        DEC A                ; DF
        DEC X                ; 46
        DEC XH               ; FD 42
        DEC XL               ; 42
        DEC Y                ; 56
        DEC YH               ; FD 52
        DEC YL               ; 52
        DEC U                ; 66
        DEC UH               ; FD 62
        DEC UL               ; 62
        DEC V                ; 76
        DEC VH               ; FD 72
        DEC VL               ; 72

        DRL (X)              ; D7
        DRL #(X)             ; FD D7

        DRR (X)              ; D3
        DRR #(X)             ; FD D3

        EAI i                ; BD 21

        HLT                  ; FD B1

        INC A                ; DD
        INC X                ; 44
        INC XH               ; FD 40
        INC XL               ; 40
        INC Y                ; 54
        INC YH               ; FD 50
        INC YL               ; 50
        INC U                ; 64
        INC UH               ; FD 60
        INC UL               ; 60
        INC V                ; 74
        INC VH               ; FD 70
        INC VL               ; 70

        ITA                  ; FD BA

        JMP ab               ; BA 06 85
        JMP tag1             ; BA 00 A9

        LDA (ab)             ; A5 06 85
        LDA (X)              ; 05
        LDA (Y)              ; 15
        LDA (U)              ; 25
        LDA (V)              ; 35
        LDA #(ab)            ; FD A5 06 85
        LDA #(X)             ; FD 05
        LDA #(Y)             ; FD 15
        LDA #(U)             ; FD 25
        LDA #(V)             ; FD 35
        LDA XH               ; 84
        LDA XL               ; 04
        LDA YH               ; 94
        LDA YL               ; 14
        LDA UH               ; A4
        LDA UL               ; 24
        LDA VH               ; B4
        LDA VL               ; 34

        LDE X                ; 47
        LDE Y                ; 57
        LDE U                ; 67
        LDE V                ; 77

        LDA i                ; B5 21
        LDI A i              ; B5 21

        LDI S ab             ; AA 06 85
        LDI XH i             ; 48 21
        LDI XL i             ; 4A 21
        LDI YH i             ; 58 21
        LDI YL i             ; 5A 21
        LDI UH i             ; 68 21
        LDI UL i             ; 6A 21
        LDI VH i             ; 78 21
        LDI VL i             ; 7A 21

        LDX P                ; FD 58
        LDX S                ; FD 48
        LDX X                ; FD 08
        LDX Y                ; FD 18
        LDX U                ; FD 28
        LDX V                ; FD 38

        LIN X                ; 45
        LIN Y                ; 55
        LIN U                ; 65
        LIN V                ; 75

        LOP UL i             ; 88 21

        NOP                  ; 38
        OFF                  ; FD 4C

        ORA (ab)             ; AB 06 85
        ORA (X)              ; 0B
        ORA (Y)              ; 1B
        ORA (U)              ; 2B
        ORA (V)              ; 3B
        ORA #(ab)            ; FD AB 06 85
        ORA #(X)             ; FD 0B
        ORA #(Y)             ; FD 1B
        ORA #(U)             ; FD 2B
        ORA #(V)             ; FD 3B

        ORA i                ; BB 21
        ORI A i              ; BB 21

        ORI (ab) i           ; EB 06 85 21
        ORI (X) i            ; 4B 21
        ORI (Y) i            ; 5B 21
        ORI (U) i            ; 6B 21
        ORI (V) i            ; 7B 21
        ORI #(ab) i          ; FD EB 06 85 21
        ORI #(X) i           ; FD 4B 21
        ORI #(Y) i           ; FD 5B 21
        ORI #(U) i           ; FD 6B 21
        ORI #(V) i           ; FD 7B 21

        POP A                ; FD 8A
        POP X                ; FD 0A
        POP Y                ; FD 1A
        POP U                ; FD 2A
        POP V                ; FD 3A

        PSH A                ; FD C8
        PSH X                ; FD 88
        PSH Y                ; FD 98
        PSH U                ; FD A8
        PSH V                ; FD B8

        RDP                  ; FD C0
        REC                  ; F9
        RIE                  ; FD BE
        ROL                  ; DB
        ROR                  ; D1
        RPU                  ; E3
        RPV                  ; B8
        RTI                  ; 8A
        RTN                  ; 9A

        SBC (ab)             ; A1 06 85
        SBC (X)              ; 01
        SBC (Y)              ; 11
        SBC (U)              ; 21
        SBC (V)              ; 31
        SBC #(ab)            ; FD A1 06 85
        SBC #(X)             ; FD 01
        SBC #(Y)             ; FD 11
        SBC #(U)             ; FD 21
        SBC #(V)             ; FD 31

        SBC XH               ; 80
        SBC XL               ; 00
        SBC YH               ; 90
        SBC YL               ; 10
        SBC UH               ; A0
        SBC UL               ; 20
        SBC VH               ; B0
        SBC VL               ; 30

        SBC i                ; B1 21
        SBI A i              ; B1 21

        SDE X                ; 43
        SDE Y                ; 53
        SDE U                ; 63
        SDE V                ; 73

        SDP                  ; FD C1
        SEC                  ; FB
        SHL                  ; D9
        SHR                  ; D5
        SIE                  ; FD 81

        SIN X                ; 41
        SIN Y                ; 51
        SIN U                ; 61
        SIN V                ; 71

        SJP ab               ; BE 06 85

        SPU                  ; E1
        SPV                  ; A8

        STA (ab)             ; AE 06 85
        STA (X)              ; 0E
        STA (Y)              ; 1E
        STA (U)              ; 2E
        STA (V)              ; 3E
        STA #(ab)            ; FD AE 06 85
        STA #(X)             ; FD 0E
        STA #(Y)             ; FD 1E
        STA #(U)             ; FD 2E
        STA #(V)             ; FD 3E
        STA XH               ; 08
        STA XL               ; 0A
        STA YH               ; 18
        STA YL               ; 1A
        STA UH               ; 28
        STA UL               ; 2A
        STA VH               ; 98
        STA VL               ; 3A

        STX P                ; FD 5E
        STX S                ; FD 4E
        STX X                ; FD 4A
        STX Y                ; FD 5A
        STX U                ; FD 6A
        STX V                ; FD 7A

        TIN                  ; F5
        TTA                  ; FD AA

        VCR i                ; C1 21
        VCS i                ; C3 21

        VEJ 0xC0             ; C0
        VEJ 0xC2             ; C2
        VEJ 0xC4             ; C4
        VEJ 0xC6             ; C6
        VEJ 0xC8             ; C8
        VEJ 0xCA             ; CA
        VEJ 0xCC             ; CC
        VEJ 0xCE             ; CE
        VEJ 0xD0             ; D0
        VEJ 0xD2             ; D2
        VEJ 0xD4             ; D4
        VEJ 0xD6             ; D6
        VEJ 0xD8             ; D8
        VEJ 0xDA             ; DA
        VEJ 0xDC             ; DC
        VEJ 0xDE             ; DE
        VEJ 0xE0             ; E0
        VEJ 0xE2             ; E2
        VEJ 0xE4             ; E4
        VEJ 0xE6             ; E6
        VEJ 0xE8             ; E8
        VEJ 0xEA             ; EA
        VEJ 0xEC             ; EC
        VEJ 0xEE             ; EE
        VEJ 0xF0             ; F0
        VEJ 0xF2             ; F2
        VEJ 0xF4             ; F4
        VEJ 0xF6             ; F6

        VHR i                ; C5 21
        VHS i                ; C7 21
        VMJ i                ; CD 21
        VVS i                ; CF 21
        VZR i                ; C9 21
        VZS i                ; CB 21

        XOR (ab)             ; AD 06 85
        XOR (X)              ; 0D
        XOR (Y)              ; 1D
        XOR (U)              ; 2D
        XOR (V)              ; 3D
        XOR #(ab)            ; FD AD 06 85
        XOR #(X)             ; FD 0D
        XOR #(Y)             ; FD 1D
        XOR #(U)             ; FD 2D
        XOR #(V)             ; FD 3D
