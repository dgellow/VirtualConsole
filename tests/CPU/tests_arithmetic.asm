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

        ;; ADC: result lesser than 0xff, but equals to 0x80 (-128)
        lda #$0f
        adc #$01

        ;; ADC: result greater than 0xff
        lda #$01
        adc #$ff

        ;; ADC: negative result (MSB = 1)
        clc
        lda #$81                ; 0x81 == -127
        adc #$01                ; 0x82 == -126

        ;; SBC: zero - zero = zero
        lda #0
        sbc #0

        ;; SBC: multiple substractions
        clc
        lda #5
        sbc #1
        sbc #1
        sbc #1
        sbc #1

        ;; SBC: result lesser than 0
        clc
        lda #$01
        sbc #$10

        ;; SBC: result greater than 0
        clc
        lda #$ff
        sbc #$01

;;; Absolute
        ;; ADC: zero + zero = zero
        clc
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

        ;; ADC: negative result (MSB = 1)
        clc
        lda #$81                ; 0x81 == -127
        sta $1020
        lda #$01
        adc $1020               ; 0x82 == -126

;;; Absolute indexed x

;;; Absolute indexed y

;;; Zeropage

;;; Zeropage indexed x

;;; Zeropage indexed y

;;; Zeropage indexed indirect

;;; Zeropage indirect indexed
