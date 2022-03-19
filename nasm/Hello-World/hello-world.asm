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
     mov al, [bx]               ; This block of code first copies the address of
     test al, al                ; what's in BX to AL (in our case the current
     je end                     ; character from the 'string'), than logically
                                ; tests (using & for each bit) if the given
                                ; character is 0. If it is than jumps to the
                                ; end because the string ended.

     push bx                    ; If the character wasn't 0, push it onto the
     mov ah, 0x0E               ; stack 'cause we need space in the registers to
     mov bx, 0x00F              ; call a BIOS routine. Than loads registers with
     int 0x10                   ; the right termnal codes and calls the BIOS'
                                ; routine.

     pop bx                     ; Restore BX register with the value that was
     inc bx                     ; previously pushed on the stack, increments it
     jmp repeat                 ; and reload jumps back to 'repeat'.

end:
     int 0x20                   ; Calls the exit command

string:
     db "Hello, world", 0
