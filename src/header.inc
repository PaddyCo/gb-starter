; Outputs the rom header
HEADER : MACRO
    db "GB Starter     "         ; Cart name - 15 characters / 15 bytes
    db $00                       ; $143 - GBC support. $00 = gb, $80 = both, $C0 = only gbc
    db 0,0                       ; $144 - Licensee code (not important)
    db 0                         ; $146 - SGB Support indicator
    db 0                         ; $147 - Cart type / MBC type (0 => no mbc)
    db 0                         ; $148 - ROM Size (0 => 32KB)
    db 0                         ; $149 - RAM Size (0 => 0KB RAM on cartridge)
    db 1                         ; $14a - Destination code
    db $33                       ; $14b - Old licensee code
    db 0                         ; $14c - Mask ROM version
    db 0                         ; $14d - Complement check (important) rgbds-fixed
    dw 0                         ; $14e - Checksum (not important)
ENDM