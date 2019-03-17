        processor 6502
        org $0000

;;; Jump and jump saving return adress
        jsr testjumpsubroutine
        jmp testjump

testjumpsubroutine:
        lda #$01
        jsr testjumpsubroutine_1
        rts

testjumpsubroutine_1:
        ldx #$02
        jsr testjumpsubroutine_2
        rts

testjumpsubroutine_2:
        ldy #$03
        rts

testjump:
        lda #$ff
        jmp testjump_1

testjump_2:
        ldy #$fd
        jmp testjump_end

testjump_1:
        ldx #$fe
        jmp testjump_2

testjump_end:
        nop
