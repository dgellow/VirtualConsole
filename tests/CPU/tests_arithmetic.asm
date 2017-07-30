        processor 6502
        org $c123

;;; Immediate
        ;; ADC: zero + zero = zero
        lda #0
        adc #0

        ;; ADC: multiple additions
        lda #0
        adc #1
        adc #1
        adc #1
        adc #1
        adc #1

        ;; ADC: result lesser than 0xff
        lda #$0f
        adc #$01

        ;; ADC: result greater than 0xff
        lda #$01
        adc #$ff

        ;; ADC: result lesser than zero
        lda #2                  ; N flag should be set by test case
        adc #1

        ;; SBC: zero - zero = zero
        lda #0
        sbc #0

        ;; SBC: multiple substractions
        lda #5
        sbc #1
        sbc #1
        sbc #1
        sbc #1
        sbc #1

        ;; SBC: result lesser than 0
        lda #$01
        sbc #$10

        ;; SBC: result greater than 0
        lda #$ff
        sbc #$01

;;; Absolute
        ;; ADC: zero + zero = zero
        lda #0
        sta $1020
        lda #0
        adc $1020

        ;; ADC: multiple additions
        lda #5
        sta $1020
        lda #0
        adc $1020
        adc $1020
        adc $1020
        adc $1020
        adc $1020

        ;; ADC: result lesser than 0xff
        lda #3
        sta $1020
        lda #$f0
        adc $1020

        ;; ADC: result greater than 0xff
        lda #$10
        sta $1020
        lda #$f0
        adc $1020

        ;; ADC: result lesser than zero
        lda #2                  ; N flag should be set by test case
        sta $1020
        lda #1
        adc $1020

;;; Absolute indexed x

;;; Absolute indexed y

;;; Zeropage

;;; Zeropage indexed x

;;; Zeropage indexed y

;;; Zeropage indexed indirect

;;; Zeropage indirect indexed
