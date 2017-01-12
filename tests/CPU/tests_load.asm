        processor 6502
        org $c123

;;; Default
        lda #0
        ldx #0
        ldy #0

;;; Immediate
        lda #22
        ldx #33
        ldy #44

;;; Immediate hex
        lda #$22
        ldx #$33
        ldy #$44

;;; Absolute
        lda $1020
        ldx $1030
        ldy $1040

;;; Absolute indexed x
        ldx #0
        lda $1020,x
        ldx #1
        lda $1020,x
        ldx #2
        lda $1020,x

        ldx #0
        ldy $1040,x
        ldx #1
        ldy $1040,x
        ldx #2
        ldy $1040,x

;;; Absolute indexed y
        ldy #0
        lda $1020,y
        ldy #1
        lda $1020,y
        ldy #2
        lda $1020,y

        ldy #0
        ldx $1030,y
        ldy #1
        ldx $1030,y
        ldy #2
        ldx $1030,y

;;; Zeropage
        lda $20
        ldx $30
        ldy $40

;;; Zeropage indexed x
        ldx #0
        lda $20,x
        ldx #1
        lda $20,x
        ldx #2
        lda $20,x

        ldx #0
        ldy $40,x
        ldx #1
        ldy $40,x
        ldx #2
        ldy $40,x

;;; Zeropage indexed y
        ldy #0
        lda $20,y
        ldy #1
        lda $20,y
        ldy #2
        lda $20,y

        ldy #0
        ldx $30,y
        ldy #1
        ldx $30,y
        ldy #2
        ldx $30,y

;;; Zeropage indexed indirect

;;; Zeropage indirect indexed
