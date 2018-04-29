//
// Created by Dell on 2018/4/24.
//

#ifndef MIPS_DIS_H
#define MIPS_DIS_H

#include "ASM.h"

using namespace std;

class dissembler
{
private:
	string file_name;
	string file_out_name;
	string state_out;
public:
	dissembler() {}
	~dissembler() {}
	void set_state() { state_out = "Disassembly success!"; }
	string get_state_out() { return state_out; }
	string get_file_out_name() { return file_out_name; }
	void read_text_addr(string i_file_name);
	int text_processing();
	string analyze(string line, int pc);
};



string dis_all(string file_addr);
string dis_state(string file_addr);


//ALU-R型  op+rs+rt+rd+shamt+op
string dis_add(string line);
string dis_sub(string line);
string dis_and(string line);
string dis_or(string line);
string dis_slt(string line);
string dis_sll(string line);
string dis_srl(string line);

//ALU-I型  op+rs+rt+numi
string dis_addi(string line);
string dis_ori(string line);
string dis_slti(string line);
string dis_lui(string line);

// 存取
string dis_lw(string line);
string dis_sw(string line);

string dis_j(string line);
string dis_jal(string line);
string dis_jr(string line);

string dis_beq(string line);
string dis_bne(string line);


string machine_to_REG(string reg);


#endif //MIPS_DIS_H
