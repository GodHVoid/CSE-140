#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <math.h>



int Hex_Decode(long decimal)
{
    int i, hexadecimal, remainder;
    for(i = 0; decimal > 0; i++){
	    remainder = decimal % 16;
	    hexadecimal += remainder * pow(10, i);
	    decimal /= 16;
    }
    return hexadecimal;
}
char *Register_Decode(long reg_num)
{
    if(reg_num == 0){
        return ("$0 = $zero");
    }else if(reg_num == 1){
        return ("$1 = $at");
    }else if(reg_num == 2){
        return ("$2 = $v0");
    }else if(reg_num == 3){
        return ("$3 = $v1");
    }else if(reg_num == 4){
        return ("$4 = $a0");
    }else if(reg_num == 5){
        return ("$5 = $a1");
    }else if(reg_num == 6){
        return ("$6 = $a2");
    }else if(reg_num == 7){
        return ("$7 = $a3");
    }else if(reg_num == 8){
        return ("$8 = $t0");
    }else if(reg_num == 9){
        return ("$9 = $t1");
    }else if(reg_num == 10){
        return ("$10 = $t2");
    }else if(reg_num == 11){
        return ("$11 = $t3");
    }else if(reg_num == 12){
        return ("$12 = $t4");
    }else if(reg_num == 13){
        return ("$13 = $t5");
    }else if(reg_num == 14){
        return ("$14 = $t6");
    }else if(reg_num == 15){
        return ("$15 = $t7");
    }else if(reg_num == 16){
        return ("$16 = $s0");
    }else if(reg_num == 17){
        return ("$17 = $s1");
    }else if(reg_num == 18){
        return ("$18 = $s2");
    }else if(reg_num == 19){
        return ("$19 = $s3");
    }else if(reg_num == 20){
        return ("$20 = $s4");
    }else if(reg_num == 21){
        return ("$21 = $s5");
    }else if(reg_num == 22){
        return ("$22 = $s6");
    }else if(reg_num == 23){
        return ("$23 = $s7");
    }else if(reg_num == 24){
        return ("$24 = $t8");
    }else if(reg_num == 25){
        return ("$25 = $t9");
    }else if(reg_num == 26){
        return ("$26 = $k0");
    }else if(reg_num == 27){
        return ("$27 = $k1");
    }else if(reg_num == 28){
        return ("$28 = $gp");
    }else if(reg_num == 29){
        return ("$29 = $sp");
    }else if(reg_num == 30){
        return ("$30 = $fp");
    }else if(reg_num == 31){
        return ("$31 = $ra");
    }else{
        return ("N/A");
    }
    return ("ERROR");
}

char *Function_Decode(long funct_code)
{
    if(funct_code == 0){
        return ("sll");
    }else if(funct_code == 2){
        return ("srl");
    }else if(funct_code == 8){
        return ("jr");
    }else if(funct_code == 32){
        return ("add");
    }else if(funct_code == 33){
        return ("addu");
    }else if(funct_code == 34){
        return ("sub");
    }else if(funct_code == 35){
        return ("subu");
    }else if(funct_code == 36){
        return ("and");
    }else if(funct_code == 37){
        return ("or");
    }else if(funct_code == 38){
        return ("xor");
    }else if(funct_code == 39){
        return ("nor");
    }else if(funct_code == 42){
        return ("slt");
    }else if(funct_code == 43){
        return ("sltu");
    }else{
        return("N/A");
    }
    return ("ERROR");
}
char *Op_Decode(long op_code_num)
{
    static char *op;
    if(op_code_num == 2){
        return ("j");
    }else if(op_code_num == 3){
        return ("jal");
    }else if(op_code_num == 4){
        return ("beq");
    }else if(op_code_num == 5){
        return ("bne");
    }else if(op_code_num == 8){
        return ("addi");
    }else if(op_code_num == 9){
        return ("addiu");
    }else if(op_code_num == 10){
        return ("slti");
    }else if(op_code_num == 11){
        return ("sltiu");
    }else if(op_code_num == 12){
        return ("andi");
    }else if(op_code_num == 13){
        return ("ori");
    }else if(op_code_num == 15){
        return ("lui");
    }else if(op_code_num == 35){
        return ("lw");
    }else if(op_code_num == 36){
        return ("lbu");
    }else if(op_code_num == 37){
        return ("lhu");
    }else if(op_code_num == 40){
        return ("sb");
    }else if(op_code_num == 41){
        return ("sh");
    }else if(op_code_num == 43){
        return ("sw");
    }else if(op_code_num == 48){
        return ("ll");
    }else if(op_code_num == 56){
        return ("sc");
    }else{
        return ("N/A");
    }
    return ("ERROR");
}
void J_instruction(char code[], int Op_code,int size)
{
    char Immediate[26];
    for (int i = 0; i < size; i++){
        if(i>=6){
            Immediate[i - 6] = code[i];
        }
    }
    printf("Instruction Type:J\n");
    char *operation = Op_Decode(Op_code);
    printf("Operation:%s\n",operation);
    //print immediate
    long address = strtol(Immediate,NULL,2);
    int add16 = Hex_Decode(address);
    printf("Immediate:%ld(or 0x00%d)\n",address,add16);
}

void I_instruction(char code[], int Op_code, int size)
{
    char RS[7], RT[6], Immediate[17];
    for (int i = 0; i < size; i++){
        //get bits for rs
        if(i>=6 && i<11){
            RS[i - 6] = code[i];
        }
        // get bits for rt
        if(i>=11 && i<16){
            RT[i - 11] = code[i];
        }
        // get bits for immediate
        if(i>=16){
            Immediate[i - 16] = code[i];
        }
    }
    printf("Instruction Type:I\n");
    // print operation
    char *operation = Op_Decode(Op_code);
    printf("Operation:%s\n",operation);
    //print rs
    int Rs_num = strtol(RS,NULL,2);
    char *rs = Register_Decode(Rs_num);
    printf("Rs:%s\n", rs);
    // print rt
    int Rt_num = strtol(RT,NULL,2);
    char *rt = Register_Decode(Rt_num);
    printf("Rt:%s\n", rt);
    // print immediate
    long imm = strtol(Immediate,NULL,2);
    int imm16 = Hex_Decode(imm);
    printf("Immediate:%ld(or 0x%d)\n", imm, imm16);
}
void R_instruction(char code[], int Op_code, int size)
{
    char RS[6], RT[6], RD[6], SHAMT[6], FUN[7];
    for (int i = 0; i < size; i++){
        //get bits for rs
        if(i>=6 && i < 11){
            RS[i - 6] = code[i];
        }
        //get bits for rt
        if(i>=11 && i<16){
            RT[i - 11] = code[i];
        }
        //get bits for rd
        if(i>=16 && i < 21){
            RD[i - 16] = code[i];
        }
        //get bits for shamt
        if(i>=21 && i < 26){
            SHAMT[i - 21] = code[i];
        }
        //get bits for function
        if(i>=26){
            FUN[i - 26] = code[i];
        }
    }
    // print type
    printf("Instruction Type:R\n");
    // binary into long
    int function = strtol(FUN,NULL,2);
    // print operation
    char *operation = Function_Decode(function);
    printf("Operation:%s\n",operation);
    // print rs
    int Rs_num = strtol(RS,NULL,2);
    char *rs = Register_Decode(Rs_num);
    printf("Rs:t%s\n", rs);
    // print rt
    int Rt_num = strtol(RT,NULL,2);
    char *rt = Register_Decode(Rt_num);
    printf("Rt:%s\n", rt);
    // print rd
    int Rd_num = strtol(RD,NULL,2);
    char *rd = Register_Decode(Rd_num);
    printf("Rd:%s\n", rd);
    // print shamt
    int shamt = strtol(SHAMT,NULL,2);
    printf("Shamt:%d\n", shamt);
    //print function
    int funct16 = Hex_Decode(function); 
    printf("Funct:%d(or 0x%d)\n", function,funct16);

}

int main()
{
    int size =32;
    char Mips_code[size], Op_code[7];
    int op_code_num;
    printf("Enter 32 bits:\n");

    for (int i = 0; i < size; i++){
        Mips_code[i] = getchar();
        if(i < 6){
            Op_code[i] = Mips_code[i];
        }
    }
    // char to long and binary to decimal
    op_code_num = strtol(Op_code,NULL,2);
    //op code number for R type code
    if(op_code_num == 0){
        R_instruction(Mips_code,op_code_num,size);
    }
    //op code number for I type code
    if(op_code_num > 3){
        I_instruction(Mips_code,op_code_num,size);
    }
    //op code number for J type code 
    if(op_code_num == 2 || op_code_num == 3){
        J_instruction(Mips_code, op_code_num,size);
    }
}
// how to compile code
// gcc filename.c -o filename -lm 