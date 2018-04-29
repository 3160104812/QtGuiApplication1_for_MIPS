//
// Created by Dell on 2018/4/25.
//
#include <sstream>
#include "ASM.h"
#include "DIS.h"

string asm_all(string file_addr)//C:\Users\chao\Desktop\notepad\1.txt
{
	assembler A;
	A.set_state();
	A.read_text_addr(file_addr);
	A.text_processing();
	A.first_scan();
	A.second_scan();

	//检查编译是否正确
	if (A.get_state_out() == "Compile successfully!")
	{
		cout << A.get_file_out_name();
		return A.get_file_out_name();
	}
	else
	{
		string s = "Error:";
		s = s + A.get_state_out();
		return s;
	}
}

string dis_all(string file_addr)
{
	dissembler D;
	int state;
	D.set_state();
	D.read_text_addr("machine.txt");
	state = D.text_processing();
	if (state == 1)
	{
		cout << D.get_file_out_name();
		return D.get_file_out_name();
	}
	else
	{
		string s = "Error:";
		s = s + D.get_state_out();
		return s;
	}
}



// 把8位二进制字符串转化成符合二进制文件读写的int
int trans_8bin_to_char(string s)
{
	// 8位二进制转十进制字符串
	string s_10;
	trans(s, s_10, 2, 10);


	// 字符串转数字
	stringstream ss;
	int num_10;
	ss << s_10;
	ss >> num_10;

	// 特定变化
	if (num_10 >127)
		num_10 = -(256 - num_10);
	return num_10;
}

string txt_to_bin()
{
	// get current path
	char path[200];
	_getcwd(path, 200);

	string s = "";
	int i = 0;
	char c = path[i];
	while (c != '\0')
	{
		s = s + c;
		i++;
		c = path[i];
	}
	string bin_addr = s + "\\bin_out.bin";
	string file_addr = s + "\\machine.txt";
	// 打开用户输入文件
	ifstream infile;
	if (!infile)
		cout << "error" << endl;
	infile.open(file_addr, ios::in);// 读, ios::in

	ofstream outfile;
	if (!outfile)
		cout << "error" << endl;
	outfile.open(bin_addr, ios::out | ios::binary);//写 没有就创建 有就清空重写

												   // 特定转化！！！
	string line, new_line;
	string line1, line2, line3, line4;
	int n1, n2, n3, n4, fsize = 0;
	char A, B, C, D;
	char N[90000];

	while (getline(infile, line))
	{
		line1 = line.substr(0, 8);
		line2 = line.substr(8, 8);
		line3 = line.substr(16, 8);
		line4 = line.substr(24, 8);

		n1 = trans_8bin_to_char(line1);
		n2 = trans_8bin_to_char(line2);
		n3 = trans_8bin_to_char(line3);
		n4 = trans_8bin_to_char(line4);

		cout << n1 << " " << n2 << " " << n3 << " " << n4 << endl;

		A = static_cast<char>(n1);
		B = static_cast<char>(n2);
		C = static_cast<char>(n3);
		D = static_cast<char>(n4);

		N[fsize] = A;
		N[fsize + 1] = B;
		N[fsize + 2] = C;
		N[fsize + 3] = D;

		fsize += 4;
	}

	//    cout <<"fsize" << fsize << endl;

	outfile.write(N, fsize);

	outfile.close();
	infile.close();
	return bin_addr;
}


string txt_to_coe()
{
	// get current path
	char path[200];
	_getcwd(path, 200);

	string s = "";
	int i = 0;
	char c = path[i];
	while (c != '\0')
	{
		s = s + c;
		i++;
		c = path[i];
	}
	string coe_addr = s + "\\coe_out.coe";
	string file_addr = s + "\\machine.txt";
	// 打开用户输入文件
	ifstream infile;
	if (!infile)
		cout << "error" << endl;
	infile.open(file_addr, ios::in);// 读, ios::in

	ofstream outfile;
	if (!outfile)
		cout << "error" << endl;
	outfile.open(coe_addr, ios::out);//写 没有就创建 有就清空重写

	outfile << "memory_initialization_radix = 16;" << endl;
	outfile << "memory_initialization_vector = " << endl;
	string line, new_line;

	getline(infile, line);
	trans(line, new_line, 2, 16);
	new_line = resize(new_line, 8);
	outfile << new_line;
	while (getline(infile, line))
	{
		outfile << "," << endl;
		trans(line, new_line, 2, 16);
		new_line = resize(new_line, 8);
		outfile << new_line; // 输入到coe_out.coe中
	}
	outfile.close();
	infile.close();
	return coe_addr;
}

string trans_char_to_8bin(int n)
{
	// 特定变化
	if (n < 0)
		n = 256 + n; // n是一个0-255的int

					 // 数字转字符串
	string s_10;
	stringstream ss;
	ss << n;
	ss >> s_10;

	string s_2;
	trans(s_10, s_2, 10, 2);

	return s_2;
}

string bin_to_txt(string file_addr)
{
	// get current path
	char path[200];
	_getcwd(path, 200);

	string s = "";
	int i = 0;
	char c = path[i];
	while (c != '\0')
	{
		s = s + c;
		i++;
		c = path[i];
	}


	// 打开用户输入文件
	ifstream infile;
	if (!infile)
		cout << "error" << endl;
	infile.open(file_addr, ios::in | ios::binary);// 读, ios::in
												  // 把指针移动到文件末端以读取文件长度 再挪回文件开头
	infile.seekg(0, ios::end);
	long int fsize = infile.tellg();
	infile.seekg(0);

	string bin_to_txt_addr = s + "\\im_bin_to_txt_out.txt";
	ofstream outfile;
	if (!outfile)
		cout << "error" << endl;
	outfile.open(bin_to_txt_addr, ios::out);//写 没有就创建 有就清空重写

											// 特定转化！！！
	char N[90000];
	infile.read(N, fsize); // 八个八个读入

	int j, n1, n2, n3, n4;
	string line1, line2, line3, line4;
	string s_2_txt;

	for (j = 0; j<fsize; j = j + 4)
	{
		n1 = static_cast<int>(N[j]);
		n2 = static_cast<int>(N[j + 1]);
		n3 = static_cast<int>(N[j + 2]);
		n4 = static_cast<int>(N[j + 3]);

		line1 = trans_char_to_8bin(n1);
		line2 = trans_char_to_8bin(n2);
		line3 = trans_char_to_8bin(n3);
		line4 = trans_char_to_8bin(n4);

		line1 = resize(line1, 8);
		line2 = resize(line2, 8);
		line3 = resize(line3, 8);
		line4 = resize(line4, 8);

		s_2_txt = line1 + line2 + line3 + line4;
		outfile << s_2_txt << endl;
	}

	outfile.close();
	infile.close();
	return bin_to_txt_addr;
}


string coe_to_txt(string file_addr)
{
	// get current path
	char path[200];
	_getcwd(path, 200);

	string s = "";
	int i = 0;
	char c = path[i];
	while (c != '\0')
	{
		s = s + c;
		i++;
		c = path[i];
	}
	string coe_to_txt_addr = s + "\\coe_to_txt_out.txt";
	// 打开用户输入文件
	ifstream infile;
	if (!infile)
		cout << "error" << endl;
	infile.open(file_addr, ios::in);// 读, ios::in

	ofstream outfile;
	if (!outfile)
		cout << "error" << endl;
	outfile.open(coe_to_txt_addr, ios::out);//写 没有就创建 有就清空重写

	string line, new_line;
	getline(infile, line); // 去掉开头的两行
	getline(infile, line);

	while (getline(infile, line))
	{
		line = line.substr(0, 8);
		trans(line, new_line, 16, 2);
		new_line = resize(new_line, 32);
		outfile << new_line << endl; // 输入到coe_to_txt_out.coe中
	}
	outfile.close();
	infile.close();
	return coe_to_txt_addr;
}

string import_to_txt(string file_addr) //把任何格式转化成txt格式
{
	string format;
	int strsize = file_addr.size();
	format = file_addr.substr(strsize - 3);
	cout << format;

	if (format == "txt")
		return file_addr;
	else if (format == "coe")
		return coe_to_txt(file_addr);
	else if (format == "bin")
		return bin_to_txt(file_addr);
	else
	{
		cout << "Wrong file format!" << endl;
		return "Wrong file format!";
	}
}