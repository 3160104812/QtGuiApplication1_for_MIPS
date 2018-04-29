//
// Created by Dell on 2018/4/25.
//
#include "DIS.h"

#include <sstream>
using namespace std;

//ALU-R型  op+rs+rt+rd+shamt+op
string dis_add(string line)
{
	string rs, rt, rd, shamt, s;
	rs = line.substr(6, 5);
	rt = line.substr(11, 5);
	rd = line.substr(16, 5);
	//    shamt = line.substr(21,5);
	rs = machine_to_REG(rs);
	rt = machine_to_REG(rt);
	rd = machine_to_REG(rd);
	//    shamt = machine_to_REG(shamt);
	s = "add " + rd + "," + rs + "," + rt;
	return s;
}

string dis_sub(string line)
{
	string rs, rt, rd, shamt, s;
	rs = line.substr(6, 5);
	rt = line.substr(11, 5);
	rd = line.substr(16, 5);
	//    shamt = line.substr(21,5);
	rs = machine_to_REG(rs);
	rt = machine_to_REG(rt);
	rd = machine_to_REG(rd);
	//    shamt = machine_to_REG(shamt);
	s = "sub " + rd + "," + rs + "," + rt;
	return s;
}

string dis_and(string line)
{
	string rs, rt, rd, shamt, s;
	rs = line.substr(6, 5);
	rt = line.substr(11, 5);
	rd = line.substr(16, 5);
	//    shamt = line.substr(21,5);
	rs = machine_to_REG(rs);
	rt = machine_to_REG(rt);
	rd = machine_to_REG(rd);
	//    shamt = machine_to_REG(shamt);
	s = "and " + rd + "," + rs + "," + rt;
	return s;
}

string dis_or(string line)
{
	string rs, rt, rd, shamt, s;
	rs = line.substr(6, 5);
	rt = line.substr(11, 5);
	rd = line.substr(16, 5);
	//    shamt = line.substr(21,5);
	rs = machine_to_REG(rs);
	rt = machine_to_REG(rt);
	rd = machine_to_REG(rd);
	//    shamt = machine_to_REG(shamt);
	s = "or " + rd + "," + rs + "," + rt;
	return s;
}

string dis_slt(string line)
{
	string rs, rt, rd, shamt, s;
	rs = line.substr(6, 5);
	rt = line.substr(11, 5);
	rd = line.substr(16, 5);
	//    shamt = line.substr(21,5);
	rs = machine_to_REG(rs);
	rt = machine_to_REG(rt);
	rd = machine_to_REG(rd);
	//    shamt = machine_to_REG(shamt);
	s = "slt " + rd + "," + rs + "," + rt;
	return s;
}

string dis_sll(string line)
{
	string rt, rd, shamt, s;
	string shamt10;
	//    rs = line.substr(6,5);
	rt = line.substr(11, 5);
	rd = line.substr(16, 5);
	shamt = line.substr(21, 5);
	// tmp二进制转十进制
	trans(shamt, shamt10, 2, 10);
	rd = machine_to_REG(rd);
	rt = machine_to_REG(rt);
	s = "sll " + rd + "," + rt + "," + shamt10;
	return s;
}
string dis_srl(string line)
{
	string rt, rd, shamt, s;
	string shamt10;
	//    rs = line.substr(6,5);
	rt = line.substr(11, 5);
	rd = line.substr(16, 5);
	shamt = line.substr(21, 5);
	// tmp二进制转十进制
	trans(shamt, shamt10, 2, 10);
	rd = machine_to_REG(rd);
	rt = machine_to_REG(rt);
	s = "sll " + rd + "," + rt + "," + shamt10;
	return s;
}

//ALU-I型  op+rs+rt+numi
string dis_addi(string line)
{
	string rs, rt, imm, s;
	rs = line.substr(6, 5);
	rt = line.substr(11, 5);
	imm = line.substr(16, 16);
	// tmp二进制转十进制
	trans(imm, s, 2, 10);
	rs = machine_to_REG(rs);
	rt = machine_to_REG(rt);
	s = "addi " + rt + "," + rs + "," + s;
	return s;
}

string dis_ori(string line)
{
	string rs, rt, imm, s;
	rs = line.substr(6, 5);
	rt = line.substr(11, 5);
	imm = line.substr(16, 16);
	// tmp二进制转十进制
	trans(imm, s, 2, 10);
	rs = machine_to_REG(rs);
	rt = machine_to_REG(rt);
	s = "ori " + rt + "," + rs + "," + s;
	return s;
}

string dis_slti(string line)
{
	string rs, rt, imm, s;
	rs = line.substr(6, 5);
	rt = line.substr(11, 5);
	imm = line.substr(16, 16);
	// tmp二进制转十进制
	trans(imm, s, 2, 10);
	rs = machine_to_REG(rs);
	rt = machine_to_REG(rt);
	s = "slti " + rt + "," + rs + "," + s;
	return s;
}

string dis_lui(string line)
{
	string rt, imm, s;
	//    rs = line.substr(6,5);
	rt = line.substr(11, 5);
	imm = line.substr(16, 16);
	// tmp二进制转十进制
	trans(imm, s, 2, 10);
	//    rs = machine_to_REG(rs);
	rt = machine_to_REG(rt);
	s = "addi " + rt + "," + s;
	return s;
}

// 存取
string dis_lw(string line)
{
	string rs, rt, imm, s;
	rs = line.substr(6, 5);
	rt = line.substr(11, 5);
	imm = line.substr(16, 16);
	// tmp二进制转十进制
	trans(imm, s, 2, 10);
	rs = machine_to_REG(rs);
	rt = machine_to_REG(rt);
	s = "sw " + rt + "," + s + "(" + rs + ")";
	return s;
}
string dis_sw(string line)
{
	string rs, rt, imm, s;
	rs = line.substr(6, 5);
	rt = line.substr(11, 5);
	imm = line.substr(16, 16);
	// tmp二进制转十进制
	trans(imm, s, 2, 10);
	rs = machine_to_REG(rs);
	rt = machine_to_REG(rt);
	s = "sw " + rt + "," + s + "(" + rs + ")";
	return s;
}

string dis_j(string line)
{
	string addr, s;
	int tmp;
	addr = line.substr(6);
	// addr二进制转十进制
	trans(addr, s, 2, 10);
	//字符串转数字
	stringstream ss;
	ss << s;
	ss >> tmp;
	// 转化
	tmp = tmp * 4;
	// 数字转字符串
	stringstream aa;
	aa << tmp;
	aa >> addr;
	s = "j " + addr;
	return s;
}
string dis_jal(string line)
{
	string addr, s;
	int tmp;
	addr = line.substr(6);
	// addr二进制转十进制
	trans(addr, s, 2, 10);
	//字符串转数字
	stringstream ss;
	ss << s;
	ss >> tmp;
	// 转化
	tmp = tmp * 4;
	// 数字转字符串
	stringstream aa;
	aa << tmp;
	aa >> addr;
	s = "jal " + addr;
	return s;
}
string dis_jr(string line)
{
	string reg, s;
	reg = line.substr(6, 5);
	reg = machine_to_REG(reg);
	s = "j " + reg;
	return s;
}

string dis_beq(string line)
{
	string rs, rt, imm, s;
	int tmp;
	rs = line.substr(6, 5);
	rt = line.substr(11, 5);
	imm = line.substr(16, 16);
	// tmp二进制转十进制
	trans(imm, s, 2, 10);
	//字符串转数字
	stringstream ss;
	ss << s;
	ss >> tmp;
	// 字节地址转字地址
	tmp = tmp * 4;
	// 数字转字符串
	stringstream aa;
	aa << tmp;
	aa >> s;

	rs = machine_to_REG(rs);
	rt = machine_to_REG(rt);
	s = "beq " + rs + "," + rt + "," + s;
	return s;
}

string dis_bne(string line)
{
	string rs, rt, imm, s;
	int tmp;
	rs = line.substr(6, 5);
	rt = line.substr(11, 5);
	imm = line.substr(16, 16);
	// tmp二进制转十进制
	trans(imm, s, 2, 10);
	//字符串转数字
	stringstream ss;
	ss << s;
	ss >> tmp;
	// 字节地址转字地址
	tmp = tmp * 4;
	// 数字转字符串
	stringstream aa;
	aa << tmp;
	aa >> s;

	rs = machine_to_REG(rs);
	rt = machine_to_REG(rt);
	s = "bne " + rs + "," + rt + "," + s;
	return s;
}



string machine_to_REG(string reg)
{
	if (reg == "00000")
		return "$zero";
	else if (reg == "00010")
		return "$v0";
	else if (reg == "00011")
		return "$v1";
	else if (reg == "00100")
		return "$a0";
	else if (reg == "00101")
		return "$a1";
	else if (reg == "00110")
		return "$a2";
	else if (reg == "00111")
		return "$a3";
	else if (reg == "01000")
		return "$t0";
	else if (reg == "01001")
		return "$t1";
	else if (reg == "01010")
		return "$t2";
	else if (reg == "01011")
		return "$t3";
	else if (reg == "01100")
		return "$t4";
	else if (reg == "01101")
		return "$t5";
	else if (reg == "01110")
		return "$t6";
	else if (reg == "01111")
		return "$t7";
	else if (reg == "10000")
		return "$s0";
	else if (reg == "10001")
		return "$s1";
	else if (reg == "10010")
		return "$s2";
	else if (reg == "10011")
		return "$s3";
	else if (reg == "10100")
		return "$s4";
	else if (reg == "10101")
		return "$s5";
	else if (reg == "10110")
		return "$s6";
	else if (reg == "10111")
		return "$s7";
	else if (reg == "11000")
		return "$t8";
	else if (reg == "11001")
		return "$t9";
	else if (reg == "11100")
		return "$gp";
	else if (reg == "11101")
		return "$sp";
	else if (reg == "11110")
		return "$fp";
	else if (reg == "11111")
		return "$ra";
	else
		return "no such register";
}