//
// Created by Dell on 2018/4/21.
//

#ifndef MIPS_HEAD_H
#define MIPS_HEAD_H

#include <iostream>
#include <fstream>
#include <vector>
#include "ASM.h"
#include <windows.h>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <direct.h>
#include <regex>

using namespace std;

class LINE
{
private:
	int PC;
	string s;
public:
	LINE(int PC, string s);
	~LINE() {}
	string get_s() { return s; }
	int get_PC() { return PC; }

};

class assembler
{
private:
	string current_file_path;
	string file_name;            // 用户输入的代码
	string file_name_process1;   // 去掉注释后的文件
	string file_out_name;
	vector<LINE*> PC_code;      // 储存正常语句的pc
	vector<LINE*> PC_tag;       // 储存main：这种语句的pc
	string state_out;
public:
	assembler() {}
	~assembler() {}

	void set_state() { state_out = "Compile successfully!"; }
	string get_state_out() { return state_out; }
	string get_file_out_name() { return file_out_name; }

	void get_current_file_path();
	void read_text_addr(string i_file_name);
	int text_processing();
	string remove_comment(string line);
	int first_scan();
	int is_tag(string line, string& tmp_s);
	int second_scan();
	string op_recognize(string op, string line);
	int find_tag(string s);

	string asm_J(string line);
	string asm_B(string line);

	string asm_j(string line);
	string asm_jal(string line);
	string asm_jr(string line);

	string asm_beq(string line);
	string asm_bne(string line);

};


string asm_all(string file_addr);
string asm_state(string file_addr);


string asm_ALU_R(string line);
string asm_ALU_S(string line);
string asm_ALU_I(string line);
string asm_L(string line);


//ALU-R型  op+rs+rt+rd+00000+op
string asm_add(string line);
string asm_sub(string line);
string asm_and(string line);
string asm_or(string line);
string asm_slt(string line);

//ALU-S型  op+rs+rt+rd+shamt+op
string asm_sll(string line);
string asm_srl(string line);

//ALU-I型  op+rs+rt+numi
string asm_addi(string line);
string asm_ori(string line);
string asm_slti(string line);
string asm_lui(string line);

// 存取
string asm_lw(string line);
string asm_sw(string line);

// 分支


// 转移



string REG(string reg);

//string dex_to_bi(string dex);
void trans(string s1, string &s2, long d1, long d2);
string resize(string s, int size);

#endif //MIPS_HEAD_H