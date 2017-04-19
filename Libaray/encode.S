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

            ldi r31,hi8(table1) ; Load high byte of table1's address

            add r30,r24 ; Add offset to address in Z register

            clr r0; clear register 0
            
            adc r31, r0 ; add the carry bit, r1 is 0 (expected)
             
            ld r24, z ; load position in table to r24
        
            ret

loadCharDecode:

            add r20, 65 ; 

	    sub r20, r22 ; 
		
	    cpi r20, 65 ;  

	    brlo wrapUp ; run the wrapUp method	    

            ld r24, r20 ; load position in table to r24

            ret


wrapUp:

	add r20, 26 ; 	
	
	ld r24, r20 ; 	

	ret



encode: subi r24, 65 ; subtract 'A' from passed parameter ; Use Z register for indirect addressing

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

	    adc r30, r1 ;

            clr r20 ; clear register 0
		
	    call checkCharDecode ;    
	
            ret


checkCharDecode:

		 
	
		ld r21, z ;
            
	        cp r21, r24 ;

            	breq loadCharDecode ;

            	inc r20 ;
		
		inc r30;

		adc r31, r1;

 	        call checkCharDecode ;

                ret

