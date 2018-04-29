//
// Created by Dell on 2018/4/21.
//

#include "ASM.h"
#include <sstream>

using namespace std;

void assembler::get_current_file_path()
{
	char path[200];
	_getcwd(path, 200);

	string s = "";
	int i = 0;
	char c = path[i];
	while (c != '\0')
	{
		s = s + c;
		// 字符串里\需要转义 碰到\就多加一个\在结尾
		        if(c == '\\')
		           s = s+ "\\";
		i++;
		c = path[i];
	}
	current_file_path = s;
	//    cout << "get path successfully!" << endl;
}

void assembler::read_text_addr(string i_file_name)
{
	this->file_name = i_file_name;
}

int assembler::text_processing()
{
	// 读入文件路径和输出文件路径
	string o_file_name = "\\text_process1.txt";
	string i_file_addr, o_file_addr;
	get_current_file_path();
	i_file_addr = current_file_path + file_name;
	o_file_addr = current_file_path + o_file_name;

	// 声明 在当前目录下创建文件outfile text_process1
	file_name_process1 = "text_process1.txt";
	ofstream outfile;
	if (!outfile)
		cout << "error" << endl;
	outfile.open(file_name_process1, ios::out);//写 没有就创建 有就清空重写

											   // 打开用户输入文件
	ifstream infile;
	if (!infile)
		cout << "error" << endl;
	infile.open(file_name, ios::in);// 读, ios::in

									// 处理infile中的每一行，去掉注释，再写入outfile中
	string line, new_line;
	while (getline(infile, line))
	{
		new_line = this->remove_comment(line);
		if (new_line == "illegal character") // 语法错误 new_line.empty() ||
		{
			state_out = "illegal character";
			return -1;
		}
		else if (!new_line.empty())     //如果这一行不为全注释，即不为空
			outfile << new_line << endl; // 输入到file_name_process1.txt中
	}
	outfile.close();
	infile.close();
	return 1; // 成功解析所有语句
}

string assembler::remove_comment(string line)
{
	string tmp_s, ret_s;
	std::smatch sm;   // 存放string结果的容器

					  // 整行为空
	std::regex re_empty("[\\s]*");
	if (regex_match(line, re_empty) == 1)
	{
		ret_s = "";
		return ret_s;
	}
	// 整行注释
	std::regex re_all_comment1("[\\s]*#.*");
	//    std::regex re_all_comment2("#.*");
	//    if(regex_match(line, re_all_comment1) == 1 || regex_match(line, re_all_comment2) == 1 )
	if (regex_match(line, re_all_comment1) == 1)
	{
		ret_s = "";
		return ret_s;
	}
	// 正常带注释的语句的处理
	std::regex re1("\\s*([a-zA-Z0-9,\\$\\(\\)\\s-]+)#.*");   // 去掉顶头空格和所有注释
	std::regex re2("\\s*([a-zA-Z0-9,\\$\\(\\)\\s-]+)");      // 不带注释的语句 不带":" 去掉顶头空格
	std::regex re3("\\s*([a-zA-Z0-9]+:)\\s*");    // 带：的语句 即类似于main：这样的语句只能由英文字母和数字组成

	if (regex_match(line, re1) == 1)
	{
		regex_search(line, sm, re1);
		tmp_s = sm[1];

		if (!tmp_s.empty())
		{
			ret_s = tmp_s;
			return ret_s;
		}
	}
	else if (regex_match(line, re2) == 1) // 捕获不带注释的正常语句
	{
		regex_search(line, sm, re2);
		tmp_s = sm[1];
		ret_s = tmp_s;
		return ret_s;
	}
	else if (regex_match(line, re3) == 1) // 捕获main:
	{
		regex_search(line, sm, re3);
		tmp_s = sm[1];

		ret_s = tmp_s;
		return ret_s;
	}
	else // 无法解析这一行语句，即输入错误。例如 带了其他非法符号，中文空格 中文逗号之类的
	{
		state_out = "illegal character";
		cout << "illegal character" << endl;
	}
}

int assembler::is_tag(string line, string& tmp_s)
{
	std::smatch sm;   // 存放string结果的容器

	std::regex re_tag("([a-zA-z0-9]+):.*");
	if (regex_match(line, re_tag) == 1)
	{
		regex_search(line, sm, re_tag);
		tmp_s = sm[1]; // 把main：匹配的main存入vector
		return 1;
	}
	else
	{
		tmp_s = line; // 把string存入vector
		return 0;
	}
}

// 把每个正常语句对应上pc，把main：这种语句标记好pc
int assembler::first_scan()
{
	LINE* p_code;
	LINE* p_tag;
	int pc = 0;
	// 打开用户去掉注释后的过程文件
	ifstream infile;
	if (!infile)
		cout << "error" << endl;
	infile.open(file_name_process1);// 读 ios::in

	string line, new_line;
	int tmp_pc;
	string tmp_s;
	while (getline(infile, line))
	{
		if (this->is_tag(line, tmp_s))// 是tag
		{
			tmp_pc = pc;
			p_tag = new LINE(tmp_pc, tmp_s);
			PC_tag.push_back(p_tag);
		}
		else // 是普通语句
		{
			tmp_pc = pc;
			p_code = new LINE(tmp_pc, tmp_s);
			pc += 4;
			PC_code.push_back(p_code);
		}
	}
	infile.close();
}


// 成功翻译全文 返回1 否则返回-1
int assembler::second_scan()
{
	string tmp_line, op, line_out;
	int i, j;
	std::smatch sm;
	std::regex re_op("([a-zA-Z]+)[\\s].*");

	file_out_name = "machine.txt";

	ofstream outfile;
	if (!outfile)
		cout << "error" << endl;
	outfile.open(file_out_name, ios::out);//写 没有文件就创建 有就清空重写

	for (i = 0; i<PC_code.size(); i++)
	{
		tmp_line = PC_code[i]->get_s();
		if (regex_match(tmp_line, re_op) == 1)
		{
			regex_search(tmp_line, sm, re_op);
			op = sm[1]; // 把匹配结果存入op
			line_out = op_recognize(op, tmp_line);  // 送入解析函数解析成机器码
													//            cout << op << "#" << tmp_line << endl; //test
			if (line_out == "grammatical mistake")  // op后续语法解析错误
			{
				state_out = "grammatical mistake";
				//                cout << "grammatical mistake" << endl;
				return -1;
			}
			else // 将机器码写入machine.txt
			{
				outfile << line_out << endl;
			}
		}
		else // 无法匹配op
		{
			state_out = "wrong operator";
			cout << "There is no such operator" << endl;
			return -1;
		}
	}
	outfile.close();
	return 1;
}

// 解析成功返回机器码，否则返回"grammatical mistake"
string assembler::op_recognize(string op, string line)
{
	string string_machine = "";
	string line_state;

	if (op == "add")
		line_state = asm_add(line);
	else if (op == "sub")
		line_state = asm_sub(line);
	else if (op == "and")
		line_state = asm_and(line);
	else if (op == "or")
		line_state = asm_or(line);
	else if (op == "sll")
		line_state = asm_sll(line);
	else if (op == "srl")
		line_state = asm_srl(line);
	else if (op == "slt")
		line_state = asm_slt(line);
	else if (op == "addi")
		line_state = asm_addi(line);
	else if (op == "ori")
		line_state = asm_ori(line);
	else if (op == "lui")
		line_state = asm_lui(line);
	else if (op == "slti")
		line_state = asm_slti(line);
	else if (op == "lw")
		line_state = asm_lw(line);
	else if (op == "sw")
		line_state = asm_sw(line);
	else if (op == "beq")
		line_state = asm_beq(line);
	else if (op == "bne")
		line_state = asm_bne(line);
	else if (op == "j")
		line_state = asm_j(line);
	else if (op == "jal")
		line_state = asm_jal(line);
	else if (op == "jr")
		line_state = asm_jr(line);

	if (line_state == "wrong") // op之后的语法有误 解析失败
	{
		state_out == "grammatical mistake";
		return "grammatical mistake";
	}
	else  // 解析成功
	{
		cout << "analyze succssfully" << endl;
		//        cout << line_state<<endl;
		string_machine = line_state;
	}

	if (string_machine.empty()) // if else语句中没有任何一个给string_machine赋值，解析失败
		return "grammatical mistake";

	return string_machine; // 解析成功
}

int assembler::find_tag(string s)
{
	int i;
	for (i = 0; i<PC_tag.size(); i++)
	{
		if (PC_tag[i]->get_s() == s) // 找到对应语句 返回PC
			return PC_tag[i]->get_PC();
	}

	return -1; // 没有找到对应语句
}


string assembler::asm_J(string line)
{
	string addr, addr_binary, tmp_s, reg;
	int pc, tmp;
	std::smatch sm;
	std::regex re_num("[a-z]+[\\s]+([0-9]+)[\\s]*");
	std::regex re_label("[a-z]+[\\s]+([a-zA-Z0-9]+)[\\s]*");


	// 直接寻址 纯数字
	if (regex_match(line, re_num) == 1)
	{
		regex_search(line, sm, re_num);
		addr = sm[1];
		// 字符串转数字
		stringstream ss;
		ss << addr;
		ss >> tmp;
		// 字寻址 例如j 10000代表着去pc为10000的地方，26位长的imm放2500.在编译的时候 是吧26位乘以四当做pc跳转
		tmp = tmp / 4;
		// 数字转字符串
		stringstream aa;
		aa << tmp;
		aa >> tmp_s;
		trans(tmp_s, addr_binary, 10, 2);      // 转化成二进制
		addr_binary = resize(addr_binary, 26);   // 补全成26位数
		return addr_binary;
	}// 寻找类似于main：这样的语句
	else if (regex_match(line, re_label) == 1)
	{
		regex_search(line, sm, re_label);
		addr = sm[1];

		// 在PC_tag中寻找是否有对应的语句
		pc = assembler::find_tag(addr);
		if (pc == -1)// 没有找到
		{
			cout << "no such tag" << endl;
			return "no such tag";
		}
		else
		{
			pc = pc / 4; // 记得除以4！！！
						 // 数字pc转化成字符串addr
			stringstream ss;
			ss << pc;
			ss >> addr;

			trans(addr, addr_binary, 10, 2);      // 转化成二进制
			addr_binary = resize(addr_binary, 26);   // 补全成26位数
			return addr_binary;
		}
	}
	else
	{
		state_out = "grammatical mistake";
		return "no such tag";
	}
}

string assembler::asm_B(string line)
{
	string rs, rt, addr, addr_binary, tmp_s, reg;
	int pc, tmp;
	std::smatch sm;
	std::regex re_num("[a-z]+[\\s]+\\$([a-z0-9]+)[\\s,]*\\$([a-z0-9]+)[\\s,]*([-]*[0-9]+)[\\s]*");
	std::regex re_label("[a-z]+[\\s]+\\$([a-z0-9]+)[\\s,]*\\$([a-z0-9]+)[\\s,]*([a-zA-Z0-9]+)[\\s]*");

	// 直接寻址 纯数字
	if (regex_match(line, re_num) == 1) {
		regex_search(line, sm, re_num);
		rs = sm[1];
		rt = sm[2];
		addr = sm[3];
		rs = REG(rs);
		rt = REG(rt);
		if (rs == "no such register" || rt == "no such register")
			return "no such register";
		// 字符串转数字
		stringstream ss;
		ss << addr;
		ss >> tmp;
		// 字寻址 例如j 10000代表着去pc为10000的地方，26位长的imm放2500.在编译的时候 是吧26位乘以四当做pc跳转
		tmp = tmp / 4;
		if (addr[0] == '-') // 如果这个addr为负数 则要根据补码的规则转换一下 在进行进制转换
		{
			tmp = 65536 + tmp;// num_2 = 2^16 - |num| = 2^16 + num;
		}
		// 数字转字符串
		stringstream aa;
		aa << tmp;
		aa >> tmp_s;
		trans(tmp_s, addr_binary, 10, 2);      // 转化成二进制
		addr_binary = resize(addr_binary, 16);   // 补全成16位数
		return rs + rt + addr_binary;
	}// 寻找类似于main：这样的语句
	else if (regex_match(line, re_label) == 1)
	{
		regex_search(line, sm, re_label);
		rs = sm[1];
		rt = sm[2];
		addr = sm[3];
		rs = REG(rs);
		rt = REG(rt);
		if (rs == "no such register" || rt == "no such register")
			return "no such register";
		// 在PC_tag中寻找是否有对应的语句
		pc = assembler::find_tag(addr);
		if (pc == -1)// 没有找到
		{
			cout << "no such tag" << endl;
			return "no such tag";
		}
		else
		{
			pc = pc / 4; // 记得除以4！！！
						 // 数字pc转化成字符串addr
			stringstream ss;
			ss << pc;
			ss >> addr;

			trans(addr, addr_binary, 10, 2);      // 转化成二进制
			addr_binary = resize(addr_binary, 16);   // 补全成16位数
			return rs + rt + addr_binary;
		}
	}
}

// 转移
string assembler::asm_j(string line)
{
	string m_code, addr;
	addr = asm_J(line);
	if (addr == "no such tag")
		return "wrong";
	m_code = "000010" + addr;
	return m_code;
}

string assembler::asm_jal(string line)
{
	string m_code, addr;
	addr = asm_J(line);
	if (addr == "no such tag")
		return "wrong";
	m_code = "000011" + addr;
	return m_code;
}


// 分支
//000100 rs rt immediate      beq $1,$2,10
string assembler::asm_beq(string line)
{
	string m_code, addr;
	addr = asm_B(line);
	if (addr == "no such tag" || addr == "no such register")
		return "wrong";
	m_code = "000100" + addr;
	return m_code;
}

string assembler::asm_bne(string line)
{
	string m_code, addr;
	addr = asm_B(line);
	if (addr == "no such tag" || addr == "no such register")
		return "wrong";
	m_code = "000101" + addr;
	return m_code;
}



LINE::LINE(int PC, string s) :
	PC(PC), s(s)
{
}