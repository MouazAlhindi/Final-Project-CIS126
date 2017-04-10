           .data ; Baudot code lookup table

table1:

             .byte 'G, 'T, 'U, 'Q, 'C, 'L, 'M, 'O, 'Z, 'V, 'K, 'N, 'S ; first half of randomized alphabet

             .byte 'P, 'D, 'J, 'B, 'W, 'Y, 'F, 'I, 'X, 'R, 'E, 'H, 'A  ; second half of randomized alphabet

             .text

             .global encode
             


encode: subi r24, 65 ; subtract 'A' from passed parameter ; Use Z register for indirect addressing

             add r24, r22 ;  add offset
             
             ldi r30,lo8(table1) ; Load low byte of table1's address

             ldi r31,hi8(table1) ; Load high byte of table1's address

             add r30,r24 ; Add offset to address in Z register

             adc r31,r1 ; add the carry bit, r1 is 0 (expected)
             
             ld r24, z ;

             ret