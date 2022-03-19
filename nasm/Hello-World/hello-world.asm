     org 0x0100                 ; This is a assembler-specific instruction, it says
                                ; that every instruction after it should start
                                ; at this address.
                                ;
                                ; 0x0100 is the start address of a COM(mand)
                                ; program.
                         
start:
     mov bx, string             ; Loading into the BX register the address
                                ; of 'string'
repeat:
     mov al, [bx]               ; Load a byte in AL from address pointed by BX
     test al, al                ; Tests AL for zero
     je end                     ; If the test is zero jump to 'end'
     push bx                    ; Save BX register in stack
     mov ah, 0x0e               ; Load AH with code for terminal output
     mov bx, 0x000f             ; BH is page zero, BL is color (graphic mode)
     int 0x10                   ; Call the BIOS for displaying one letter
     pop bx                     ; Restore BX register from stack
     inc bx                     ; Increase the BX register by 1
     jmp repeat                 ; Jumps to 'repeat'

end:
     int 0x20                   ; Calls the exit command

string:
     db "Hello, world", 0
