#pragma once
#pragma execution_character_set("utf-8")
#include <QtWidgets/QMainWindow>
#include "ui_notepad.h"

class Notepad : public QMainWindow
{
	Q_OBJECT

public:
	Notepad(QWidget *parent = Q_NULLPTR);

private:
	Ui::NotepadClass ui;
	QString curFile;
	QString curResult;
	bool A_D_mode;//true:assembler

	private slots:
	void compile_clicked();
	bool open_called();
	bool OPEN(const QString FILE_NAME);

	bool save_called();
	bool saveas_called();
	bool SAVE(const QString FILE_NAME);

	void assembler_called();
	void dissembler_called();
	bool DISPLAY(const QString FILE_NAME);

	void switch_called();

	void change_fontsize_edit();
	void change_fontsize_browser();

	void export_bin_called();
	void export_coe_called();

	void EXPORT(const char type);
	

};
