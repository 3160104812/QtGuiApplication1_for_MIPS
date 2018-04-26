#include "notepad.h"
#include "txt_handle.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication MIPSApp(argc, argv);
	Notepad MIPS;
	MIPS.show();

	return MIPSApp.exec();
}