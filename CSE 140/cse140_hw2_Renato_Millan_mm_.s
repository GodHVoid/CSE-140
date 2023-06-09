# Traditional Matrix Multiply program
.data
matrix_a:
		.word   1,  2,  3,  4,  5,  6,  7,  8,  9,  
  		.word  13, 14, 15, 16, 17, 18, 19, 20, 21,  
  		.word  25, 26, 27, 28, 29, 30, 31, 32, 33,  
  		.word  37, 38, 39, 40, 41, 42, 43, 44, 45,  
  		.word  49, 50, 51, 52, 53, 54, 55, 56, 57,  
  		.word  61, 62, 63, 64, 65, 66, 67, 68, 69,  
  		.word  73, 74, 75, 76, 77, 78, 79, 80, 81,  
  		.word  85, 86, 87, 88, 89, 90, 91, 92, 93,  
  		.word  97, 98, 99,100,101,102,103,104,105 

matrix_b:
		.word 133,134,135,136,137,138,139,140,141, 
  		.word 121,122,123,124,125,126,127,128,129, 
  		.word 109,110,111,112,113,114,115,116,117, 
  		.word  97, 98, 99,100,101,102,103,104,105, 
  		.word  85, 86, 87, 88, 89, 90, 91, 92, 93,  
  		.word  73, 74, 75, 76, 77, 78, 79, 80, 81,  
  		.word  61, 62, 63, 64, 65, 66, 67, 68, 69,  
  		.word  49, 50, 51, 52, 53, 54, 55, 56, 57,  
  		.word  37, 38, 39, 40, 41, 42, 43, 44, 45  

matrix_c:
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,   
  		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,   
  		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,   
  		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,   
  		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,   
  		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,   
  		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,   
 		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,   
  		.word   0,  0,  0,  0,  0,  0,  0,  0,  0   

n:		.word 9

nline:  .asciiz "\n"				#Define new line string
sp:		.asciiz " "
msga: 	.asciiz "Matrix A is: \n"
msgb: 	.asciiz "Matrix B is: \n"
msgc: 	.asciiz "Matrix C=A*B is: \n"

		.text
		.globl main
main:

		la	$s1, n # load n in %s1
		lw	$s1, 0($s1) #store n 
		la	$s2, matrix_a
		la	$s3, matrix_b
		la	$s4, matrix_c

		la	$a0, msga
		la 	$a1, matrix_a
		jal	PRINT_MAT 
		la	$a0, msgb
		la 	$a1, matrix_b
		jal	PRINT_MAT 

# Your CODE HERE
		# s1 = n
		li $t0,4
		li $t1,0 #i =0	
loop1:	bge	$t1,$s1,end1 # matrix is done
		li $t2,0 #j=0
loop2:	bge	$t2,$s1,end2
		li $s6,0  # sum =0
		j loop3		
mult_store:	
		mul $t3,$t1,$s1
		mul $t3,$t3,$t0
		mul $t4,$t2,$t0
		add $t3,$t3,$t4
		sw $s6,	matrix_c($t3)
		addi $t2,$t2,1 #j++
		li $t5,0 # k =0
		j loop2
		
loop3:	bge	$t5,$s1, mult_store
		#A[i,k]
		mul $t6, $t1,$s1
		mul $t6,$t6,$t0
		mul $t7, $t5,$t0
		add $t6,$t6,$t7
		lw $t6, matrix_a($t6)
		#B[K][J]
		mul $t8,$t5,$s1
		mul $t8,$t8,$t0
		mul $t9,$t2,$t0
		add $t8,$t8,$t9
		lw $t8, matrix_b($t8)
		mul $t8,$t6,$t8
		add $s6,$s6,$t8
		addi $t5,$t5,1 #k++
		j loop3
end2:		
		addi $t1,$t1,1 #i++
		j loop1	
		

# End CODE

end1:		la	$a0, msgc
		la 	$a1, matrix_c
		jal	PRINT_MAT 

#   Exit
		li	 $v0,10
    	syscall


PRINT_MAT:	li	$v0,4
		syscall
		addi $a2,$0,0	
PL4:	bge	$a2,$s1,PL1
		addi $a3,$0,0
PL3:	bge	$a3,$s1,PL2

		lw	$a0,0($a1)
		li	$v0,1
		syscall
		la	$a0,sp
		li	$v0,4
		syscall
		addi $a1,$a1,4
		addi $a3,$a3,1
		b 	PL3

PL2:	addi	$a2,$a2,1
		la	$a0,nline
		li	$v0,4
		syscall
		b	PL4
PL1:	jr	$ra
