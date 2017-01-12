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

        lda #$22
        ldx #$33
        ldy #$44

;;; Absolute
