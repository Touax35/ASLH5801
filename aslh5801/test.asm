
        .globl offset
        n       =       0x20
        i       =       0x21        

        ANI A n      ; B9 i
        BII A i      ; BF i
        LDI A i      ; B5 i
        ORI A i      ; BB i
        SBI A i      ; B1 i

        AND n      ; B9 i
        BIT i      ; BF i
        LDA i      ; B5 i
        ORA i      ; BB i
        SBC i      ; B1 i


