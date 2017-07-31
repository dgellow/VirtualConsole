        processor 6502
        org $c123

;;; Carry
        sec
        clc

;;; Decimal mode
        sed
        cld

;;; Interrupt disable status
        sei
        cli

;;; Overflow
        sec
        lda #$80
        sbc #$01                ; Set V flag
        clv                     ; Clear V flag
