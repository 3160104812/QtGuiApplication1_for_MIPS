#pragma execution_character_set("utf-8")

#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <string>
#include "notepad.h"
#include "top.h"

Notepad::Notepad(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	curFile = tr("untitled.txt");
	curResult = tr("not defined");
	A_D_mode = true;// control the trans direction
	setWindowTitle(curFile);
	/*
	ui.textEdit->setFont(QFont(tr("Consolas"), 14));
	ui.textBrowser->setFont(QFont(tr("Consolas"), 14));
	*/
	QFont font;
	font.setFamily("Consolas");
	font.setFixedPitch(true);
	font.setPointSize(14);
	ui.textEdit->setFont(font);
	ui.textBrowser->setFont(font);//seting font
}
bool Notepad::open_called()
{
	QString filename = QFileDialog::getOpenFileName(this, "open the file");
	QString title_tmp = filename;
	
	std::string str = import_to_txt(filename.toStdString());
	if (str == "Wrong file format!")
	{
		QMessageBox::warning(this, "Warning", "Wrong file format!");
		return false;
	}
	filename = QString::fromStdString(str);
	if (filename.isEmpty() || filename==curFile)
	{
		QMessageBox::warning(this, "Warning", "Already opened~~");
		return false;
	}
	else
	{
		setWindowTitle(title_tmp);
		return OPEN(filename);
	}
}
bool Notepad::OPEN(const QString FILE_NAME)
{
	QFile fp(FILE_NAME);
	QTextStream fin(&fp);
	if (!fp.open(QFile::ReadOnly | QFile::Text))
	{
		QMessageBox::warning(this, "Warning", "Cannot open : " + fp.errorString());
		return false;
	}
	QString text = fin.readAll();
	ui.textEdit->setText(text);
	curFile = QFileInfo(FILE_NAME).canonicalFilePath();
	fp.close();
	return true;
}

bool Notepad::save_called()
{	
	if (curFile == tr("untitled.txt"))
	{
		return saveas_called();
	}
	if (ui.textEdit->document()->isModified())
	{
		return SAVE(curFile);
	}
	else return true;
}
bool Notepad::saveas_called()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("save as"), curFile);
	if (filename.isEmpty())
	{
		return false;
	}
	else return SAVE(filename);
}
bool Notepad::SAVE(const QString FILE_NAME)
{
	QFile fp(FILE_NAME);
	QTextStream fout(&fp);
	if (!fp.open(QFile::WriteOnly | QFile::Text))
	{
		QMessageBox::warning(this, "Warning", "Cannot save : " + fp.errorString());
		return false;
	}
	QString text = ui.textEdit->toPlainText();
	fout << text;
	curFile = QFileInfo(FILE_NAME).canonicalFilePath();
	setWindowTitle(curFile);
	fp.close();
	QMessageBox msg;//提示窗口
	QString line = curFile;
	msg.setText(line);
	msg.setWindowTitle(tr("saved successfully!"));
	msg.show();
	msg.exec();
	return true;
}

void Notepad::assembler_called()
{
	save_called();
	if (A_D_mode == false)switch_called();
	std::string str = curFile.toStdString();
	str = asm_all(str);
	curResult = QString::fromStdString(str);
	DISPLAY(QString::fromStdString(str));
}
void Notepad::dissembler_called()
{
	save_called();
	if (A_D_mode == true)switch_called();
	std::string str = curFile.toStdString();//x现在函数体是一样的
	str = dis_all(str);
	curResult = QString::fromStdString(str);
	DISPLAY(QString::fromStdString(str));
}
bool Notepad::DISPLAY(const QString FILE_NAME)
{
	std::string line = FILE_NAME.toStdString();
	if (!strncmp(&line[0],"Error:",6))
	{
		QMessageBox::warning(this,"ERROR",FILE_NAME);
		return false;
	}
	QFile fp(FILE_NAME);
	QTextStream fin(&fp);
	if (!fp.open(QFile::ReadOnly | QFile::Text))
	{
		QMessageBox::warning(this, "Warning", "Cannot open : " + fp.errorString());
		return false;
	}
	QString text = fin.readAll();
	ui.textBrowser->setText(text);
	fp.close();
	return true;
}

void Notepad::switch_called()
{
	A_D_mode = !A_D_mode;
	if (A_D_mode)
	{
		ui.mode->setText(tr("assembler"));
	}
	else
	{
		ui.mode->setText(tr("dissembler"));
	}
	return;
}

void Notepad::change_fontsize_edit()
{
	ui.textEdit->setFont(QFont(tr("Consolas"), qint32(ui.size_edit->value())));
}
void Notepad::change_fontsize_browser()
{
	ui.textBrowser->setFont(QFont(tr("Consolas"), qint32(ui.size_browser->value())));
}

void Notepad::export_bin_called()
{
	EXPORT('b');
}
void Notepad::export_coe_called()
{
	EXPORT('c');
}
void Notepad::EXPORT(const char type)
{
	if (curResult==QString::fromStdString("not defined"))
	{
		return;
	}
	std::string export_file_name;
	if (type == 'c')
	{
		export_file_name = txt_to_coe();
		QMessageBox::warning(this, "Warning", QString::fromStdString(export_file_name));
	}
	else if (type == 'b')
	{
		export_file_name = txt_to_bin();
		QMessageBox::warning(this, "Warning", QString::fromStdString(export_file_name));
	}
	
	QString filename = QFileDialog::getSaveFileName(this, tr("save as"), QString::fromStdString(export_file_name));
	if (filename.isEmpty())
	{
		return;
	}
	else
	{
		QFile fp(filename);
		QFile fe(QString::fromStdString(export_file_name));
		
		QTextStream fout(&fp);
		QTextStream fin(&fe);
		if (!fp.open(QFile::WriteOnly | QFile::Text)||!fe.open(QFile::ReadOnly | QFile::Text))
		{
			QMessageBox::warning(this, "Warning", "Cannot save : " + fp.errorString());
			return ;
		}
		QString text = fin.readAll();
		fout << text;
		fp.close();
		fe.close();
		QMessageBox msg;//提示窗口
		QString line = filename;
		msg.setText(line);
		msg.setWindowTitle(tr("Exported successfully!"));
		msg.show();
		msg.exec();
	}
}

void Notepad::compile_clicked()
{
	if (A_D_mode == true)
	{
		assembler_called();
	}
	else
	{
		dissembler_called();
	}
}
