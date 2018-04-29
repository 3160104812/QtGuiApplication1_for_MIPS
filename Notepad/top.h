//
// Created by Dell on 2018/4/26.
//


#pragma once

#include <string>
#include "ASM.h"
#include "DIS.h"

using namespace std;

string asm_all(std::string file_addr);
string dis_all(std::string file_addr);

// export
string txt_to_bin();
string txt_to_coe();
int trans_8bin_to_char(string s);

// import
string import_to_txt(string file_addr); //把任何格式转化成txt格式
string bin_to_txt(string file_addr);
string coe_to_txt(string file_addr);
string trans_char_to_8bin(int n);