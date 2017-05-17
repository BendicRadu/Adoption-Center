#ifndef GUI_H
#define GUI_H

#include <qlistwidget.h>
#include <qlist.h>
#include <qtextstream.h>
#include <qlabel.h>
#include <qboxlayout.h>
#include <qcheckbox.h>
#include <qformlayout.h>
#include <qradiobutton.h>
#include <QtWidgets/QMainWindow>
#include "ui_myclass.h"
#include <qpushbutton.h>
#include "Ctrl.h"
#include "outputDog.h"
#include <qdebug.h>
#include <qapplication.h>
#include <qdesktopwidget.h>
#include <qtimer.h>
#include <Qpoint>
#include <qpointer.h>
#include <qlineedit.h>
#include <sstream>
#include <qmessagebox.h>

class GUI : public QMainWindow
{
	Q_OBJECT

public:
	GUI ( Controller& c, QWidget *parent = 0);
	~GUI();
	
	void setButton();
	void setFile();
	void choseMode();
	void setMode();
	void adminMode();
	void userMode();
	const char* toChar(Dog* d);
	void refresh(std::vector<Dog> d);
	void refreshNext(Dog d);
	void add();
	void choseUpdate();
	void update();

private:
	Ui::MyClassClass ui;
	Controller& ctrl;
	std::vector<QRadioButton*> qRadPtr;
	std::vector<QWidget*> windows;
	std::vector<QListWidget* > list;
	QListWidget* wList1;
	QListWidget* wList2;
	QPushButton* button1;
	QPushButton* button2;
	QPushButton* button3;
};

#endif // GUI_H
