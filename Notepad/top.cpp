//
// Created by Dell on 2018/4/25.
//
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
    if(A.get_state_out() == "Compile successfully!")
    {
        cout<<A.get_file_out_name();
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
    if(state == 1)
    {
        cout<<D.get_file_out_name();
        return D.get_file_out_name();
    }
    else
    {
		string s = "Error:";
		s = s + D.get_state_out();
        return s;
    }
}
