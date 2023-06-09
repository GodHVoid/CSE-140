#include <string>
#include <stdlib.h>
#include <ctype.h>
#include <limits>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <cstring>
//Global variable pc init here
int pc = 0;
int registerfile[32];
int Dmem[32];
std::string RegDst = "0";
int Branch = 0;
int MemRead = 0;
std::string memto_Reg = "0";
std::string AlUop = "00";
int MemWrite = 0;
int ALUSrC = 0;
int RegWrite = 0;
int jump = 0;
int ALUzero =0;
int sign_extend =0;
std::string ALU_Con= "0000";
long long op_code_num = 0;
long long RS = 0;
long long RT = 0;
int function = 0;
long long IMM = 0;
long long RD = 0;
long SHAMT = 0;
long long address = 0;
int total_clock_cycles = 0;
int branchtarget = 0;
int PC4 = 0;
int destination = 0;


std::string op_c(std::string instruction);
long Shamt(std::string instruction);
long Rd(std::string instruction);
long Rs(std::string instruction);
long Rt(std::string instruction);
int func(std::string instrunction);
int immediate(std::string instruction);
void control_unit( std:string type);
int next_pc(int pc);
std::string Register_Decode(int reg_num);
void writeBack(int ALUresult);
void getinfo();
void writeBack(int ALUresult);
void mem(int index);
void execute(std::string instruction);
void decode(std::string instruction);
void fetch(std::vector<std::string> instructions, int row);
//Op-code
std::string op_c(std::string instruction){
	std::string op_code;
	op_code = instruction.substr(0,6);
	std::cout <<"INSTRUCTION CODE: "<< instruction << "\n";
	return op_code;
}
long Shamt(std::string instruction){
    std::string shamt;
	shamt = instruction.substr(21,5);
	std::cout <<"shaamt: "<< shamt << "\n";
    return std::stoi(rs, nullptr,2);
}
long Rd(std::string instruction){
    std::string rd;
	rd = instruction.substr(16,5);
	std::cout <<"Rd: "<< rd << "\n";
    return std::stoi(rs, nullptr,2);
}
long Rs(std::string instruction){
    std::string rs;
	rs = instruction.substr(6,5);
	std::cout <<"Rs: "<< rs << "\n";
    return std::stoi(rs, nullptr,2);
}
long Rt(std::string instruction){
    std::string rt;
	rt = instruction.substr(11,5);
	std::cout <<"Rt: "<< rt << "\n";
	return std::stoi(rt, nullptr,2);
}
int func(std::string instrunction){
    std::string func;
    func = instruction.substr(26,6);
    return std:stoi(func,nullptr,2);
    
}
int immediate(std::string instruction){
    std::string imm;
    imm = instruction.substr(16,16);
    //extend.push_back(instruction.substr(16,16));
    return imm;
}
void control_unit( std::string type){
    if(op_code_num == 0)
    {
        RegDst = "1";
        ALUSrC = 0;
        memto_Reg= "0";
        RegWrite = 1;
        MemRead = 0;
        MemWrite = 0;
        Branch = 0;
        AlUop = "10";
        if(func == 32)
        {
            ALU_Con = "0010";
        }
        else if(func == 34)
        {
            ALU_Con = "0110";
        }
        else if(func == 36)
        {
            ALU_Con = "0000";
        }
        else if(func == 37)
        {
            ALU_Con = "0001";
        }
        else if(func == 29){
            ALU_Con = "1100";
        }
        else{
            ALU_Con = "0111";
        }
        
    }
    if(op_code_num > 3)
    {
        if(op_code_num == 35){
            RegDst = "0";
            ALUSrC = 1;
            memto_Reg= "1";
            RegWrite = 1;
            MemRead = 0;
            MemWrite = 0;
            Branch = 0;
            AlUop = "00";
            ALU_Con = "0010";
        }else if (op_code_num == 43){
            RegDst = "x";
            ALUSrC = 1;
            memto_Reg= "x";
            RegWrite = 0;
            MemRead = 0;
            MemWrite = 1;
            Branch = 0;
            AlUop = "00";
             ALU_Con = "0010";
        }else{
            RegDst = "x";
            ALUSrC = 0;
            memto_Reg= "x";
            RegWrite = 0;
            MemRead = 0;
            MemWrite = 0;
            Branch = 1;
            AlUop = "01";
             ALU_Con = "0110";
        }
    }
    if (op_code_num == 2 || op_code_num == 3){
        jump = 1;
        RegDst = "0";
        ALUSrC = 0;
        memto_Reg= "0";
        RegWrite = 0;
        MemRead = 0;
        MemWrite = 0;
        Branch = 0;
        AlUop = "xx";
    }
}
int next_pc(int pc){
return pc+4;
}
std::string Register_Decode(int reg_num)
{
    if(reg_num == 0){
        return ("$zero");
    }else if(reg_num == 1){
        return ("$at");
    }else if(reg_num == 2){
        return ("$v0");
    }else if(reg_num == 3){
        return ("$v1");
    }else if(reg_num == 4){
        return ("$a0");
    }else if(reg_num == 5){
        return ("$a1");
    }else if(reg_num == 6){
        return ("$a2");
    }else if(reg_num == 7){
        return ("$a3");
    }else if(reg_num == 8){
        return ("$t0");
    }else if(reg_num == 9){
        return ("$t1");
    }else if(reg_num == 10){
        return ("$t2");
    }else if(reg_num == 11){
        return ("$t3");
    }else if(reg_num == 12){
        return ("$t4");
    }else if(reg_num == 13){
        return ("$t5");
    }else if(reg_num == 14){
        return ("$t6");
    }else if(reg_num == 15){
        return ("$t7");
    }else if(reg_num == 16){
        return ("$s0");
    }else if(reg_num == 17){
        return ("$s1");
    }else if(reg_num == 18){
        return ("$s2");
    }else if(reg_num == 19){
        return ("$s3");
    }else if(reg_num == 20){
        return ("$s4");
    }else if(reg_num == 21){
        return ("$s5");
    }else if(reg_num == 22){
        return ("$s6");
    }else if(reg_num == 23){
        return ("$s7");
    }else if(reg_num == 24){
        return ("$t8");
    }else if(reg_num == 25){
        return ("$t9");
    }else if(reg_num == 26){
        return ("$k0");
    }else if(reg_num == 27){
        return ("$k1");
    }else if(reg_num == 28){
        return ("$gp");
    }else if(reg_num == 29){
        return ("$sp");
    }else if(reg_num == 30){
        return ("$fp");
    }else if(reg_num == 31){
        return ("$ra");
    }else{
        return ("N/A");
    }
    return ("ERROR");
}
void getinfo(){

    printf("Total Clock Cycles: %d", total_clock_cycles);
    if(op_code_num = 0){
        std::string register_name = Register_Decode(RD);
        printf(register_name + " is modified to 0x%x\n",registerfile[RD]);
        printf("PC is modified to 0x%x\n",PC);
    }else if(op_code_num == 35){
        std::string register_name = Register_Decode(RT);
        printf(register_name + " is modified to 0x%x\n",registerfile[RT]);
        printf("PC is modified to 0x%x\n",PC);
    }else if (op_code_num == 43){
        printf("Memory 0x%x is modified to 0x%x\n",destination*4, registerfile[RT]);
        printf("PC is modified to 0x%x\n",PC);
    }else if (op_code_num == 4){
        printf("PC is modified to 0x%x\n",PC);
    }else if (op_code_num == 2){
        printf("PC is modified to 0x%x\n",PC);
    }
}
void writeBack(int ALUresult){
    PC = PC4;
    if(op_code_num == 0){
        registerfile[RD] = ALUresult;
    }
    else if(op_code_num == 35){
        registerfile[RT] = ALUresult;
    }
    else if(op_code_num == 4)
    {
        if(branchtarget != 0){
            PC = ALUresult;
        }
    }
    else if(op_code_num == 2){
        PC = ALUresult;
    }
    total_clock_cycles++;
    getinfo();
}
void mem(int index){
    if(op_code_num == 35){
        writeBack(Dmem[index]);
    }
    else if(op_code_num == 43){
        Dmem[index] = registerfile[RT];
    }
    
}
//Use stol to get decimal values.
void execute(std::string instruction){
    if(AlUop == "10"){
        if(ALU_Con == "0010"){
            writeBack(registerfile[RS] + registerfile[RT]);
        }
        else if(ALU_Con == "0110"){
            writeBack(registerfile[RS] - registerfile[RT]);
        }
        else if(ALU_Con =="0000"){
            writeBack(registerfile[RS] & registerfile[RT]);
        }
        else if(ALU_Con =="0001")
        {
           writeBack(registerfile[RS] | registerfile[RT]);
        }
        else if (ALU_Con == "1100")
        {
            writeBack(!(registerfile[RS] | registerfile[RT]));
        }
        else if(ALU_Con == "0111")
            writeBack(registerfile[RS] < registerfile[RT]);
        }else{
            return 0;
        }
    }
    else if(AlUop =="00")
    {
        if(ALU_Con == "0010"){
            destination = registerfile[RS] + sign_extend;
            mem(destination);
        }
        if(ALU_Con =="0110"){
            if(registerfile[RS] - registerfile[RT] == 0){
                ALUzero = 1;
                sign_extend = IMM < 4;
                sign_extend = sign_extend *4;
                branchtarget = PC4 + 4 + sign_extend;
                writeBack(branchtarget);
            }
        }
    }
    else if(AlUop == "xx")
    {
        writeBack(PC + address);
    }
}    
void decode(std::string instruction){
	//We first determine the instruction type by getting the opcode.
    std:string type;
    op_code_num = std::stoi(op_c(instruction), nullptr,2);
    std::cout << "opcode number is: " << op_code_num << "\n";
    //Place conditions for R,I, and J types.
    //R type instructions == 0
    if(op_code_num == 0){
        //RFormat(Mips_code,op_code_num);
        type = "R";
        RS =Rs(instruction);
        std::cout << "rs: " << rs << "\n";
        RT =Rt(instruction);
        std::cout << "rt: " << rt << "\n" ;
        RD = Rd(instruction);
        function = func(instruction);
        SHAMT = Shamt(instruction);
    }

    //I type instructions >3
    if(op_code_num > 3){
        //IFormat(Mips_code,op_code_num);
        type = "I";
        rs =Rs(instruction);
        std::cout << "rs: " << rs << "\n";
        rt =Rt(instruction);
        std::cout << "rt: " << rt << "\n";
        IMM = immediate(instruction);
        std::cout << "sign extend imm: " <<IMM<< "\n";
        sign_extend = IMM * 4

    }
    //J type instructions
    if(op_code_num == 2 || op_code_num == 3){
        type = "J";
        address = instruction.substr(6,24);
        std::cout << "address: " <<address<< "\n";
        //JFormat(Mips_code, op_code_num);
    }
    control_unit(type);
    execute(instruction);

    //For sign extend, add ffff0000. (for i-format code)

}
void fetch(std::vector<std::string> instructions, int row){
	//First we take in the big instruction array and specifically copy the row we are looking to fetch.
	std::string instruction = instructions[row];
	//std::cout << "Testing fetch: " << instructions[row] << "\n"; // Successful implementation, now we need to iterate over the string.
	//Call decode here
    PC4 = next_pc(PC);
    decode(instruction);
}






int main(){
	//Init strings to read, hold data that we will log through.
    //registerfile=0;
    for(int i =0;i<32;i++){
        registerfile[i] = 0;
        Dmem[i] = 0;
    }
    registerfile[9]=32;
    registerfile[10] = 5;
    registerfile[16] = 112;
    Dmem[28] = 5;
    Dmem[29] = 16;
	std::string lineReader;
	std::vector <std::string> outputLines; //Location of parsed material
	std::vector<int> output;
	std::string fileName = "sample_part1.txt"; // Please change this to whatever file you would like to read. Scanf maybe.
	//For this instance, we are reading sample_part1.txt, however we can just change the var above.
	std::ifstream input(fileName, std::ifstream::binary);
	//Iterators in order to determine when to stop.
	//Read the file, push result into outputLines.
	while(std::getline(input, lineReader)){
		outputLines.push_back(lineReader);
	}
	//printf("The file contents are: \n");
	/*for(int i = 0; i < outputLines.size();i++){
		for(int j = 0; j < outputLines[i].size();j++){
			std::cout << outputLines[i][j];
		}
	}
	*/
	//std::cout << "file contents: " << "\n";
	/*for(int i = 0; i < outputLines.size();i++){
		std::cout << outputLines[i] << "\n";
	}
	*/
	//The biggest part, doing the entire single-cycle in a loop.
	for(int i = 0; i < outputLines.size(); i++){
		//We will fetch the first instruction.
		fetch(outputLines,i);
        
        


	}
    printf("program terminated:\n");
    printf("Total execution time is %d cycles", total_clock_cycles);
	/*for(auto i: outputLines){
		std::cout << "The file contents are: \n";
		std::cout << i;
	}
	*/
	return 0;
}



//To run this file, do g++ Project1.cpp -o (whatever you want file name to be).exe