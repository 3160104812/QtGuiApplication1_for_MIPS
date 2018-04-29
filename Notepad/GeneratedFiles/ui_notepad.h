/********************************************************************************
** Form generated from reading UI file 'notepad.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTEPAD_H
#define UI_NOTEPAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NotepadClass
{
public:
    QAction *actionassembler;
    QAction *actiondissembler;
    QAction *actionsave;
    QAction *actionsave_as;
    QAction *actionopen;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QTextEdit *textEdit;
    QTextBrowser *textBrowser;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QSlider *size_edit;
    QPushButton *pushButton_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QSlider *size_browser;
    QGridLayout *gridLayout;
    QPushButton *pushButton_4;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QLabel *mode_lable;
    QLabel *mode;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *change_mode;
    QMenuBar *menuBar;
    QMenu *menuEdit;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *NotepadClass)
    {
        if (NotepadClass->objectName().isEmpty())
            NotepadClass->setObjectName(QStringLiteral("NotepadClass"));
        NotepadClass->resize(1000, 781);
        actionassembler = new QAction(NotepadClass);
        actionassembler->setObjectName(QStringLiteral("actionassembler"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Notepad/Notepad.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionassembler->setIcon(icon);
        actiondissembler = new QAction(NotepadClass);
        actiondissembler->setObjectName(QStringLiteral("actiondissembler"));
        actiondissembler->setIcon(icon);
        actionsave = new QAction(NotepadClass);
        actionsave->setObjectName(QStringLiteral("actionsave"));
        actionsave->setIcon(icon);
        actionsave_as = new QAction(NotepadClass);
        actionsave_as->setObjectName(QStringLiteral("actionsave_as"));
        actionsave_as->setIcon(icon);
        actionopen = new QAction(NotepadClass);
        actionopen->setObjectName(QStringLiteral("actionopen"));
        actionopen->setIcon(icon);
        centralWidget = new QWidget(NotepadClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        horizontalLayout->addWidget(textEdit);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setSearchPaths(QStringList());

        horizontalLayout->addWidget(textBrowser);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        size_edit = new QSlider(centralWidget);
        size_edit->setObjectName(QStringLiteral("size_edit"));
        size_edit->setMinimum(1);
        size_edit->setMaximum(30);
        size_edit->setValue(12);
        size_edit->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(size_edit);


        verticalLayout->addLayout(horizontalLayout_3);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);


        horizontalLayout_5->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        size_browser = new QSlider(centralWidget);
        size_browser->setObjectName(QStringLiteral("size_browser"));
        size_browser->setMinimum(1);
        size_browser->setMaximum(30);
        size_browser->setValue(12);
        size_browser->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(size_browser);


        verticalLayout_2->addLayout(horizontalLayout_4);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 0, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


        horizontalLayout_5->addLayout(verticalLayout_2);


        gridLayout_2->addLayout(horizontalLayout_5, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 25, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        mode_lable = new QLabel(centralWidget);
        mode_lable->setObjectName(QStringLiteral("mode_lable"));

        horizontalLayout_2->addWidget(mode_lable);

        mode = new QLabel(centralWidget);
        mode->setObjectName(QStringLiteral("mode"));

        horizontalLayout_2->addWidget(mode);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        change_mode = new QPushButton(centralWidget);
        change_mode->setObjectName(QStringLiteral("change_mode"));

        horizontalLayout_2->addWidget(change_mode);


        gridLayout_2->addLayout(horizontalLayout_2, 3, 0, 1, 1);

        NotepadClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(NotepadClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 26));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        NotepadClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(NotepadClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        NotepadClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(NotepadClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        NotepadClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuEdit->addAction(actionassembler);
        menuEdit->addAction(actiondissembler);
        menuFile->addAction(actionopen);
        menuFile->addSeparator();
        menuFile->addAction(actionsave);
        menuFile->addAction(actionsave_as);

        retranslateUi(NotepadClass);
        QObject::connect(pushButton, SIGNAL(clicked()), NotepadClass, SLOT(compile_clicked()));
        QObject::connect(actionsave, SIGNAL(triggered()), NotepadClass, SLOT(save_called()));
        QObject::connect(actionsave_as, SIGNAL(triggered()), NotepadClass, SLOT(saveas_called()));
        QObject::connect(actionopen, SIGNAL(triggered()), NotepadClass, SLOT(open_called()));
        QObject::connect(actionassembler, SIGNAL(triggered()), NotepadClass, SLOT(assembler_called()));
        QObject::connect(actiondissembler, SIGNAL(triggered()), NotepadClass, SLOT(dissembler_called()));
        QObject::connect(change_mode, SIGNAL(clicked()), NotepadClass, SLOT(switch_called()));
        QObject::connect(size_edit, SIGNAL(valueChanged(int)), NotepadClass, SLOT(change_fontsize_edit()));
        QObject::connect(size_browser, SIGNAL(valueChanged(int)), NotepadClass, SLOT(change_fontsize_browser()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), NotepadClass, SLOT(open_called()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), NotepadClass, SLOT(export_bin_called()));
        QObject::connect(pushButton_4, SIGNAL(clicked()), NotepadClass, SLOT(export_coe_called()));

        QMetaObject::connectSlotsByName(NotepadClass);
    } // setupUi

    void retranslateUi(QMainWindow *NotepadClass)
    {
        NotepadClass->setWindowTitle(QApplication::translate("NotepadClass", "Notepad", nullptr));
        actionassembler->setText(QApplication::translate("NotepadClass", "assembler", nullptr));
#ifndef QT_NO_SHORTCUT
        actionassembler->setShortcut(QApplication::translate("NotepadClass", "Ctrl+Shift+A", nullptr));
#endif // QT_NO_SHORTCUT
        actiondissembler->setText(QApplication::translate("NotepadClass", "dissembler", nullptr));
#ifndef QT_NO_SHORTCUT
        actiondissembler->setShortcut(QApplication::translate("NotepadClass", "Ctrl+D", nullptr));
#endif // QT_NO_SHORTCUT
        actionsave->setText(QApplication::translate("NotepadClass", "save", nullptr));
#ifndef QT_NO_SHORTCUT
        actionsave->setShortcut(QApplication::translate("NotepadClass", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionsave_as->setText(QApplication::translate("NotepadClass", "save as", nullptr));
#ifndef QT_NO_SHORTCUT
        actionsave_as->setShortcut(QApplication::translate("NotepadClass", "Ctrl+Shift+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionopen->setText(QApplication::translate("NotepadClass", "open", nullptr));
#ifndef QT_NO_SHORTCUT
        actionopen->setShortcut(QApplication::translate("NotepadClass", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        textEdit->setPlaceholderText(QApplication::translate("NotepadClass", "Code......", nullptr));
        textBrowser->setPlaceholderText(QApplication::translate("NotepadClass", "Waiting......", nullptr));
        label->setText(QApplication::translate("NotepadClass", "FontSize", nullptr));
        pushButton_3->setText(QApplication::translate("NotepadClass", "ImportCode", nullptr));
        label_2->setText(QApplication::translate("NotepadClass", "FontSize", nullptr));
        pushButton_4->setText(QApplication::translate("NotepadClass", "coe", nullptr));
        pushButton_2->setText(QApplication::translate("NotepadClass", "bin", nullptr));
        pushButton->setText(QApplication::translate("NotepadClass", "go->", nullptr));
        mode_lable->setText(QApplication::translate("NotepadClass", "mode:", nullptr));
        mode->setText(QApplication::translate("NotepadClass", "assemble", nullptr));
        change_mode->setText(QApplication::translate("NotepadClass", "change", nullptr));
        menuEdit->setTitle(QApplication::translate("NotepadClass", "Edit", nullptr));
        menuFile->setTitle(QApplication::translate("NotepadClass", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NotepadClass: public Ui_NotepadClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTEPAD_H
