        processor 6502
        org $c123

;;; nop
        nop
        nop
        nop
        nop
        nop

        nop
        lda #$12
        nop
        sec
        nop

;;; Break
        break
