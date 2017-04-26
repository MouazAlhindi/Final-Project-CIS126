           .data ; Baudot code lookup table
table1:

             .byte 'G, 'T, 'U, 'Q, 'C, 'L, 'M, 'O, 'Z, 'V, 'K, 'N, 'S ; first half of randomized alphabet

             .byte 'P, 'D, 'J, 'B, 'W, 'Y, 'F, 'I, 'X, 'R, 'E, 'H, 'A  ; second half of randomized alphabet

             .text


             .global checkCharDecode

             .global loadCharDecode

             .global loadCharEncode
                
             .global encode

             .global wrapDown

             .global decrypt
	     
             .global wrapUp
             
loadCharEncode:

            ldi r30,lo8(table1) ; Load low byte of table1's address

            ldi r31,hi8(table1) ; Load high byte of table1's address (line 30)

            add r30,r24 ; Add offset to address in Z register

            clr r0; clear register 0
            
            adc r31, r0 ; add the carry bit, r1 is 0 (expected)
             
            ld r24, z ; load position in table to r24
        
            ret

loadCharDecode:

            clr r20 ;

	    ldi r20, 65;

	    add r25, r20 ;

	    sub r25, r22 ;
		
            cpi r25, 65;

            brlo wrapUp ; run the wrapUp method (line 50)

            mov r24, r25 ; load position in table to r24

            ret


wrapUp:
        clr r28 ;
	
	ldi r28, 26 ;

        add r25, r28;
	
        mov r24, r25 ;

        ret



encode:

            subi r24, 65 ; subtract 'A' from passed parameter ; Use Z register for indirect addressing

            add r24, r22 ;  add offset

            cpi r24, 26 ; compare position to length of list

            brsh wrapDown ; branch if greater or equal too, run the wrapDown method

            call loadCharEncode ;

            ret

wrapDown:
            subi r24, 26 ; subtract by 26 and set the char back to the start
            
            call loadCharEncode ;
            
            ret

decrypt:
            ldi r30,lo8(table1) ; Load low byte of table1's address

            ldi r31,hi8(table1) ; Load high byte of table1's address

	    clr r1 ;

            adc r30, r1 ;

            clr r25 ; clear register 25
		
            call checkCharDecode ;
	
            ret


checkCharDecode:
	
            ld r21, z+ ;

            cp r21, r24 ;

            breq loadCharDecode ;

            inc r25 ;

            rjmp checkCharDecode ;

            ret