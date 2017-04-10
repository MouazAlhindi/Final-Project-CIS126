           .data ; Baudot code lookup table

table1:

             .byte 'G, 'T, 'U, 'Q, 'C, 'L, 'M, 'O, 'Z, 'V, 'K, 'N, 'S ; first half of randomized alphabet

             .byte 'P, 'D, 'J, 'B, 'W, 'Y, 'F, 'I, 'X, 'R, 'E, 'H, 'A  ; second half of randomized alphabet

             .text


             .global encode

             .global wrap

             .global decode
             


encode: subi r24, 65 ; subtract 'A' from passed parameter ; Use Z register for indirect addressing

             add r24, r22 ;  add offset
             
             ldi r30,lo8(table1) ; Load low byte of table1's address

             ldi r31,hi8(table1) ; Load high byte of table1's address

             cpi r24, 26 ; compare position to length of list

             brpl wrap ; branch if plus, run the wrap method

             add r30,r24 ; Add offset to address in Z register

             clr r0; clear register 0

             adc r31, r0 ; add the carry bit, r1 is 0 (expected)
             
             ld r24, z ; load position in table to r24

             ret

wrap:
            sub r24, 26;

            ret

decode:

            
            ret