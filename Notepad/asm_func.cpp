//
// Created by Dell on 2018/4/23.
//
#include <sstream>
#include "ASM.h"
// 解析成功 返回01组成的字符串；否则返回“wrong”


string asm_ALU_R(string line)
{
	string rs, rt, rd;
	std::smatch sm;
	std::regex re("[a-z]+[\\s]+\\$([a-z0-9]+)[\\s,]*\\$([a-z0-9]+)[\\s,]*\\$([a-z0-9]+)[\\s]*");

	if (regex_match(line, re) == 1)
	{
		regex_search(line, sm, re);
		rd = sm[1];
		rs = sm[2];
		rt = sm[3];
	}
	rs = REG(rs);
	rt = REG(rt);
	rd = REG(rd);
	if (rs == "no such register" || rt == "no such register" || rd == "no such register")
		return "no such register";
	return rs + rt + rd;
}

string asm_ALU_S(string line)
{
	string rt, rd, shamt, shamt_binary;
	std::smatch sm;
	std::regex re("[a-z]+[\\s]+\\$([a-z0-9]+)[\\s,]*\\$([a-z0-9]+)[\\s,]*([0-9]+)[\\s]*");

	if (regex_match(line, re) == 1)
	{
		regex_search(line, sm, re);
		rd = sm[1];
		rt = sm[2];
		shamt = sm[3];
	}
	rt = REG(rt);
	rd = REG(rd);
	trans(shamt, shamt_binary, 10, 2);      // 转化成二进制
	shamt_binary = resize(shamt_binary, 5);   // 补全成5位数

	if (rt == "no such register" || rd == "no such register")
		return "no such register";
	return rt + rd + shamt_binary;
}

string asm_ALU_I(string line)
{
	string rs, rt, num, num_binary;
	std::smatch sm;
	std::regex re("[a-z]+[\\s]+\\$([a-z0-9]+)[\\s,]*\\$([a-z0-9]+)[\\s,]*([-]*[0-9]+)[\\s]*");

	if (regex_match(line, re) == 1)
	{
		regex_search(line, sm, re);
		rt = sm[1];
		rs = sm[2];
		num = sm[3];
	}
	rs = REG(rs);
	rt = REG(rt);
	if (num[0] == '-') // 如果这个imm为负数 则要根据补码的规则转换一下 在进行进制转换
	{
		stringstream nn, mm;
		int num_2, num_old_int;
		nn << num;  // string 转 int
		nn >> num_old_int;
		num_2 = 65536 + num_old_int;// num_2 = 2^16 - |num| = 2^16 + num;
		mm << num_2; // int 转 string
		mm >> num;
	}
	trans(num, num_binary, 10, 2);      // 转化成二进制
	num_binary = resize(num_binary, 16);   // 补全成16位数

	return rs + rt + num_binary;
}

string asm_L(string line)
{
	string rs, rt, num, num_binary;
	std::smatch sm;
	std::regex re("[a-z]+[\\s]+\\$([a-z0-9]+)[\\s,]*([-]*[0-9]+)\\(\\$([a-z0-9]+)\\)[\\s,]*[\\s]*");

	if (regex_match(line, re) == 1)
	{
		regex_search(line, sm, re);
		rt = sm[1];
		rs = sm[3];
		num = sm[2];
	}
	rs = REG(rs);
	rt = REG(rt);
	if (num[0] == '-') // 如果这个imm为负数 则要根据补码的规则转换一下 在进行进制转换
	{
		stringstream nn, mm;
		int num_2, num_old_int;
		nn << num;  // string 转 int
		nn >> num_old_int;
		num_2 = 65536 + num_old_int;// num_2 = 2^16 - |num| = 2^16 + num;
		mm << num_2; // int 转 string
		mm >> num;
	}
	trans(num, num_binary, 10, 2);      // 转化成二进制
	num_binary = resize(num_binary, 16);   // 补全成16位数

	return rs + rt + num_binary;
}




// ALU-R型 op+rs+rt+rd+00000+op
string asm_add(string line)
{
	string m_code, rs_rt_rd;
	rs_rt_rd = asm_ALU_R(line);
	if (rs_rt_rd == "no such register")
		return "wrong";
	m_code = "000000" + rs_rt_rd + "00000" + "100000";
	return m_code;
}

string asm_sub(string line)
{
	string m_code, rs_rt_rd;
	rs_rt_rd = asm_ALU_R(line);
	if (rs_rt_rd == "no such register")
		return "wrong";
	m_code = "000000" + rs_rt_rd + "00000" + "100010";
	return m_code;
}

string asm_and(string line)
{
	string m_code, rs_rt_rd;
	rs_rt_rd = asm_ALU_R(line);
	if (rs_rt_rd == "no such register")
		return "wrong";
	m_code = "000000" + rs_rt_rd + "00000" + "100100";
	return m_code;
}

string asm_or(string line)
{
	string m_code, rs_rt_rd;
	rs_rt_rd = asm_ALU_R(line);
	if (rs_rt_rd == "no such register")
		return "wrong";
	m_code = "000000" + rs_rt_rd + "00000" + "100101";
	return m_code;
}

string asm_slt(string line)
{
	string m_code, rs_rt_rd;
	rs_rt_rd = asm_ALU_R(line);
	if (rs_rt_rd == "no such register")
		return "wrong";
	m_code = "000000" + rs_rt_rd + "00000" + "101010";
	return m_code;
}


// ALU-S型 op+rs+rt+rd+shamt+op
string asm_sll(string line)
{
	string m_code, rt_rd_shamt;
	rt_rd_shamt = asm_ALU_S(line);
	if (rt_rd_shamt == "no such register")
		return "wrong";
	m_code = "00000000000" + rt_rd_shamt + "000000";
	return m_code;
}

string asm_srl(string line)
{
	string m_code, rt_rd_shamt;
	rt_rd_shamt = asm_ALU_S(line);
	if (rt_rd_shamt == "no such register")
		return "wrong";
	m_code = "00000000000" + rt_rd_shamt + "000010";
	return m_code;
}


//ALU-I型 op+rs+rt+imm
string asm_addi(string line)
{
	string m_code, rs_rt_num;
	rs_rt_num = asm_ALU_I(line);
	if (rs_rt_num == "no such register")
		return "wrong";
	m_code = "001000" + rs_rt_num;
	return m_code;
}

string asm_ori(string line)
{
	string m_code, rs_rt_num;
	rs_rt_num = asm_ALU_I(line);
	if (rs_rt_num == "no such register")
		return "wrong";
	m_code = "001101" + rs_rt_num;
	return m_code;
}

string asm_slti(string line)
{
	string m_code, rs_rt_num;
	rs_rt_num = asm_ALU_I(line);
	if (rs_rt_num == "no such register")
		return "wrong";
	m_code = "001010" + rs_rt_num;
	return m_code;
}

// lui $1,100   op：001111 rs:00000 rt immediate
string asm_lui(string line)
{
	string m_code, rt_num;


	string rt, num, num_binary;
	std::smatch sm;
	std::regex re("[a-z]+[\\s]+\\$([a-z0-9]+)[\\s,]*([0-9]+)[\\s]*");

	if (regex_match(line, re) == 1)
	{
		regex_search(line, sm, re);
		rt = sm[1];
		num = sm[2];
	}
	rt = REG(rt);
	trans(num, num_binary, 10, 2);      // 转化成二进制
	num_binary = resize(num_binary, 16);   // 补全成16位数
	rt_num = rt + num_binary;

	if (rt_num == "no such register")
		return "wrong";
	m_code = "00111100000" + rt_num;
	return m_code;
}


// 存取
// 100011 rs rt immediate     lw $1,10($2)
string asm_lw(string line)
{
	string m_code, rs_rt_num;
	rs_rt_num = asm_L(line);
	if (rs_rt_num == "no such register")
		return "wrong";
	m_code = "100011" + rs_rt_num;
	return m_code;
}

string asm_sw(string line)
{
	string m_code, rs_rt_num;
	rs_rt_num = asm_L(line);
	if (rs_rt_num == "no such register")
		return "wrong";
	m_code = "101011" + rs_rt_num;
	return m_code;
}

// 分支
//000100 rs rt immediate      beq $1,$2,10


// 转移
string assembler::asm_jr(string line)
{
	string reg;
	int pc, tmp;
	std::smatch sm;
	std::regex re_reg("[a-z]+[\\s]+\\$([a-zA-Z0-9]+)[\\s]*");
	if (regex_match(line, re_reg) == 1)
	{
		regex_search(line, sm, re_reg);
		reg = sm[1];
		reg = REG(reg);
		if (reg == "no such register")
			return "wrong";
		else
			return "000000" + reg + "000000000000000001000";
	}
	else
		return "wrong";
}


//register = {'zero':0,'v0':2,'v1':3,'a0':4,'a1':5,'a2':6,'a3':7,'t0':8,'t1':9,'t2':10,
//'t3':11,'t4':12,'t5':13,'t6':14,'t7':15,'s0':16,'s1':17,'s2':18,'s3':19,
//'s4':20,'s5':21,'s6':22,'s7':23,'t8':24,'t9':25,'gp':28,'sp':29,'fp':30,'ra':31}
string REG(string reg)
{
	if (reg == "zero")
		return "00000";
	else if (reg == "v0")
		return "00010";
	else if (reg == "v1")
		return "00011";
	else if (reg == "a0")
		return "00100";
	else if (reg == "a1")
		return "00101";
	else if (reg == "a2")
		return "00110";
	else if (reg == "a3")
		return "00111";
	else if (reg == "t0")
		return "01000";
	else if (reg == "t1")
		return "01001";
	else if (reg == "t2")
		return "01010";
	else if (reg == "t3")
		return "01011";
	else if (reg == "t4")
		return "01100";
	else if (reg == "t5")
		return "01101";
	else if (reg == "t6")
		return "01110";
	else if (reg == "t7")
		return "01111";
	else if (reg == "s0")
		return "10000";
	else if (reg == "s1")
		return "10001";
	else if (reg == "s2")
		return "10010";
	else if (reg == "s3")
		return "10011";
	else if (reg == "s4")
		return "10100";
	else if (reg == "s5")
		return "10101";
	else if (reg == "s6")
		return "10110";
	else if (reg == "s7")
		return "10111";
	else if (reg == "t8")
		return "11000";
	else if (reg == "t9")
		return "11001";
	else if (reg == "gp")
		return "11100";
	else if (reg == "sp")
		return "11101";
	else if (reg == "fp")
		return "11110";
	else if (reg == "ra")
		return "11111";
	else
		return "no such register";
}

// d1进制转d2进制 s1输入 s2输出 输出字符串长度为size 不够就补0
void trans(string s1, string &s2, long d1, long d2)
{
	//思路，还是将原数转换成十进制数 -> 再由十进制数转换成目标进制的数
	long i, j, t, num;
	char c;
	num = 0;
	//先转换成十进制数
	for (i = 0; i < s1.size(); i++) {
		if (s1[i] >= '0'&&s1[i] <= '9') {
			t = s1[i] - '0';
		}
		else t = s1[i] - 'A' + 10;
		//参考十进制的方式
		num = num * d1 + t;
	}
	i = 0;
	s2 = "";
	while (1)
	{
		t = num % d2;
		num /= d2;
		if (t <= 9)s2 = to_string(t) + s2;
		else s2 = (char)((t - 10 + 'A')) + s2;
		if (num == 0)break;
	}
}

// 把二进制数补全成指定长度
string resize(string s, int size)
{
	int old_size = s.size();

	if (old_size < size)
	{
		for (int i = 0; i < size - old_size; i++)
			s = "0" + s;
	}
	return s;
}