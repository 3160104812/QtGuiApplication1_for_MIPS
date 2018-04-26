#include "txt_handle.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

std::string func(std::string file_path)
{
	std::string line;

	fstream  afile;
	fstream  anotherfile;
	afile.open(file_path, ios::out | ios::in);
	anotherfile.open("C:\\Users\\chao\\Desktop\\temp.txt", ios::out);//这里可以指定其他temp的位置
	while (getline(afile, line))
	{
		anotherfile << line << "     done!" << endl;
	}
	afile.close();
	anotherfile.close();

	return std::string("C:\\Users\\chao\\Desktop\\temp.txt");
}
