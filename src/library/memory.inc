INCLUDE_MEMCOPY : MACRO
; Copies a section of memory
;
; **Inputs**
;
; * `hl` - Memory location you want to copy data **to**
; * `de` - Memory location you want to copy data **from**
; * `bc` - How many bytes you want to copy
;
; **Registers**
;
; * `a` - Last piece of data copied
; * `de` - Address of last byte copied from
; * `hl` - Address of last byte copied to
; * `bc` - `$00`
Memcopy:
    ld a, [de] ; Grab 1 byte from the source
    ld [hli], a ; Place it at the destination, incrementing hl
    inc de ; Move to next byte
    dec bc ; Decrement count
    ld a, b ; Check if count is 0, since `dec bc` doesn't update flags
    or c
    jr nz, Memcopy
	ret
ENDM

INCLUDE_MEMCOPYSTOPATZERO : MACRO
; Copies a a section of memory, stopping when reaching a 0.
; Useful for copying strings or other things of unknown length
;
; **Inputs**
; 
; * `hl` - Memory location you want to copy data **to**
; * `de` - Memory location you want to copy data **from**
;
; **Registers**
;
; * `a` - Last piece of data copied
; * `de` - Address of last byte copied from
; * `hl` - Address of last byte copied to
MemcopyStopAtZero:
    ld a, [de] ; Grab 1 byte from the source
    ld [hli], a ; Place it at the destination, incrementing hl
    inc de ; Move to next byte
	and a ; Check if the byte we just copied is zero
    jr nz, MemcopyStopAtZero
	ret
ENDM