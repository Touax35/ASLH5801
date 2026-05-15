        .title Test of LH5801 assembler

	.lh5801v

        n  =        0x20
        nn =        0x0584
        ab =        0x0685
        i  =        0x21

        ;***********************************************************
        ADC VL               ; 32
        ADC VH               ; B2
        ADC (V)              ; 33
        ADC# (V)             ; FD 33
        ADI (V) n            ; 7F 20
        ADI #(V) n           ; FD 7F 20
        ADR V                ; FD FA
        AND (V)              ; 39
        AND #(V)             ; FD 39
        ANI (V) i            ; 79 21
        ANI #(V) i           ; FD 79 21
        BII (V) i            ; 7D 21
        BII #(V) i           ; FD 7D 21
        BIT (V)              ; 3F
        BIT #(V)             ; FD 3F
        CPA (V)              ; 37
        CPA #(V)             ; FD 37
        CPA VH               ; B6
        CPA VL               ; 36
        CPI VH i             ; 7C 21
        CPI VL i             ; 7E 21
        DCA (V)              ; BC
        DCA #(V)             ; FD BC
        DCS (V)              ; 3C
        DCS #(V)             ; FD 3C
        DEC V                ; 76
        DEC VH               ; FD 72
        DEC VL               ; 72
        INC V                ; 74
        INC VH               ; FD 70
        INC VL               ; 70
        LDA (V)              ; 35
        LDA #(V)             ; FD 35
        LDA VH               ; B4
        LDA VL               ; 34
        LDE V                ; 77
        LDI VH i             ; 78 21
        LDI VL i             ; 7A 21
        LDX V                ; FD 38
        LIN V                ; 75
        ORA (V)              ; 3B
        ORA #(V)             ; FD 3B
        ORI (V) i            ; 7B 21
        ORI #(V) i           ; FD 7B 21
        POP V                ; FD 3A
        PSH V                ; FD B8
        SBC (V)              ; 31
        SBC #(V)             ; FD 31
        SBC VH               ; B0
        SBC VL               ; 30
        SDE V                ; 73
        SIN V                ; 71
        STA (V)              ; 3E
        STA #(V)             ; FD 3E
        STA VH               ; 98
        STA VL               ; 3A
        STX V                ; FD 7A
        XOR (V)              ; 3D
        XOR #(V)             ; FD 3D
