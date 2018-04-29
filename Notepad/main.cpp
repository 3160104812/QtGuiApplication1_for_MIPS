#include "notepad.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication MIPSApp(argc, argv);
	Notepad MIPS;
	MIPS.show();

	return MIPSApp.exec();
}