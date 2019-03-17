        processor 6502
        org $c123

;;; Absolute
        lda #1
        ldx #2
        ldy #3

        sta $1020
        stx $1021
        sty $1022

;;; Absolute indexed x
        lda #99
        ldx #0
        sta $1030,x
        ldx #1
        sta $1030,x
        ldx #2
        sta $1030,x

;;; Absolute indexed y
        lda #88

        ldy #0
        sta $1040,y
        ldy #1
        sta $1040,y
        ldy #2
        sta $1040,y

;;; Zeropage
        lda #1
        ldx #2
        ldy #3

        sta $20
        stx $21
        sty $22

;;; Zeropage indexed x
        lda #77

        ldx #0
        sta $30,x
        ldx #1
        sta $30,x
        ldx #2
        sta $30,x

        ldy #66

        ldx #0
        sty $40,x
        ldx #1
        sty $40,x
        ldx #2
        sty $40,x

;;; Zeropage indexed y
        ldx #55

        ldy #0
        stx $50,y
        ldy #1
        stx $50,y
        ldy #2
        stx $50,y

;;; Zeropage indexed indirect
        lda #44

        ldx #0
        sta ($60,x)
        ldx #10
        sta ($60,x)

;;; Zeropage indirect indexed
        lda #33

        ldy #0
        sta ($70),y
        ldy #10
        sta ($70),y
