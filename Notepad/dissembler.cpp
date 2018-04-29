//
// Created by Dell on 2018/4/24.
//
#include "DIS.h"
#include <sstream>
using namespace std;
void dissembler::read_text_addr(string i_file_name)
{
	this->file_name = i_file_name;
}

int dissembler::text_processing()
{
	// 读入文件路径和输出文件路径
	//    string o_file_name = "\\text_process1.txt";
	//    string i_file_addr,o_file_addr;
	//    get_current_file_path();
	//    i_file_addr = current_file_path + file_name;
	//    o_file_addr = current_file_path + o_file_name;

	// 声明 在当前目录下创建文件outfile text_process1
	file_out_name = "mipscode.txt";
	ofstream outfile;
	if (!outfile)
		cout << "error" << endl;
	outfile.open(file_out_name, ios::out);//写 没有就创建 有就清空重写

										  // 打开用户输入文件
	ifstream infile;
	if (!infile)
		cout << "error" << endl;
	infile.open(file_name, ios::in);// 读, ios::in

									// 处理infile中的每一行，去掉注释，再写入outfile中
	string line, new_line;
	int pc = 0;
	while (getline(infile, line))
	{
		if (line.size() != 32)
		{
			state_out = "size is wrong";
			return -1;
		}
		else
		{
			new_line = analyze(line, pc);
			pc += 4;
			outfile << new_line << endl;
		}
	}
	outfile.close();
	infile.close();
	return 1; // 成功解析所有语句
}

string dissembler::analyze(string line, int pc)
{
	string op, op2, PC;
	string ret_code, ret = "                         # PC=    ";

	//pc转成字符串
	stringstream aa;
	aa << pc;
	aa >> PC;

	//get op
	op = line.substr(0, 6);
	op2 = line.substr(14, 6);

	if (op == "000000") //R型
	{
		op2 = line.substr(26, 6);
		if (op2 == "100000")
			ret_code = dis_add(line);
		else if (op2 == "100010")
			ret_code = dis_sub(line);
		else if (op2 == "100100")
			ret_code = dis_and(line);
		else if (op2 == "100101")
			ret_code = dis_or(line);
		else if (op2 == "101010")
			ret_code = dis_slt(line);
		else if (op2 == "000000")
			ret_code = dis_sll(line);
		else if (op2 == "000010")
			ret_code = dis_srl(line);
	}
	else if (op == "001000")
		ret_code = dis_addi(line);
	else if (op == "001101")
		ret_code = dis_ori(line);
	else if (op == "001010")
		ret_code = dis_slti(line);
	else if (op == "001111")
		ret_code = dis_lui(line);
	else if (op == "100011")
		ret_code = dis_lw(line);
	else if (op == "101011")
		ret_code = dis_sw(line);
	else if (op == "000000")
		ret_code = dis_jr(line);
	else if (op == "000011")
		ret_code = dis_jal(line);
	else if (op == "000010")
		ret_code = dis_j(line);
	else if (op == "000101")
		ret_code = dis_bne(line);
	else if (op == "000100")
		ret_code = dis_beq(line);
	else
		ret_code = "wrong";

	if (ret_code == "wrong")
		return "wrong";
	else
	{
		ret_code.resize(25, ' ');    // code补成24位长的，不够的补空格
		ret.replace(0, 25, ret_code); // code补到钱25位
		ret.replace(31, 4, PC);       // 后面几位是#PC =
		return ret;
	}
}