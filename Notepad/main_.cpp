#include "ASM.h"
#include "DIS.h"
using namespace std;


int main()
{
    //四个接口函数 分别是 汇编 反汇编 汇编控制台输出 反汇编控制台输出

    asm_all("test.txt");
    dis_all("machine.txt");
    asm_state("test.txt");
    dis_state("machine.txt");


}
