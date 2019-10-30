INCLUDE "header.inc"
INCLUDE "vendor/hardware.inc"
INCLUDE "library/memory.inc"

SECTION "memory library", ROM0
    INCLUDE_MEMCOPY
    INCLUDE_MEMCOPYSTOPATZERO


; ROM is given control from boot here
SECTION "rom entry point", ROM0[$0100]
    nop
    jp Main

; Contains the header
SECTION "rom header", ROM0[$0104]
    ; nintendo logo is required here or gameboy will lock
    NINTENDO_LOGO 
    ; Header defined in header.inc
    HEADER

SECTION "main", ROM0
Main:
; Wait for VBlank before turning off LCD. Turning off LCD display outside of VBlank WILL damage the display on real hardware.
.waitVBlank
    ld a, [rLY]
    cp 144 ; Check if the LCD is past VBlank
    jr c, .waitVBlank

    ; Turn off LCD
    xor a ; ld a, $00
    ld [rLCDC], a

    ; Copy font tiles
    ld hl, $9000 ; Destination address 
    ld de, FontTiles ; From address
    ld bc, FontTilesEnd - FontTiles ; Length
    call Memcopy

    ; Copy string
    ld hl, _SCRN0 + 256 + 4
    ld de, HelloWorldString 
    call MemcopyStopAtZero

    ; Setup palette
    ld a, %11100100
    ld [rBGP], a

    ; Reset scroll
    xor a ; ld a, $00
    ld [rSCX], a
    ld [rSCY], a

    ; Turn sound off (This will reduce battery consumption by ~16%, remove if you are using sound)
    ld [rNR52], a

    ; Turn screen on, display background
    ld a, LCDCF_ON | LCDCF_BGON
    ld [rLCDC], a

    ; Loop forever
.forever
    jr .forever

SECTION "font", ROM0
FontTiles:
INCBIN "font.chr"
FontTilesEnd:

SECTION "hello world string", ROM0
HelloWorldString:
    db "Hello World!", 0 ; Append 0, which signals the end of the string
