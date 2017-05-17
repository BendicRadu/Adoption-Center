#include "GUI.h"

GUI::GUI( Controller& c, QWidget *parent): QMainWindow(parent), ctrl(c) {
	ui.setupUi(this);
	
	this->wList1 = new QListWidget(this);
	this->wList2 = new QListWidget(this);

	wList1->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(wList1, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(ShowContextMenu(QPoint)));

	setButton();
}

GUI::~GUI(){}


//----------------------------------UTILS---------------------------------------------------//

Dog* toUI(Dog& d) { return new UiDog(d.getBreed(), d.getName(), d.getAge(), d.getWeight(), d.getPhoto()); }
QString toQstr(Dog* d) { return d->toQstr(); }
const char* GUI::toChar(Dog* d) { return  d->toStr().c_str(); }


void GUI::refresh(std::vector<Dog> d) {

	QRect rec = QApplication::desktop()->screenGeometry();
	QSize sz(rec.width() - 900 , rec.height() - 900);
	
	wList1->clear();

	for (int i = 0; i < d.size(); i++) {
		Dog* dp = toUI(d[i]);
		std::string str = dp->toStr();
		
		QListWidgetItem *newItem = new QListWidgetItem;
		newItem->setText(QString::fromStdString(str));
		newItem->setSizeHint(sz);
		wList1->insertItem(i, newItem);

	}

}

void GUI::refreshNext(Dog d) {

	QRect rec = QApplication::desktop()->screenGeometry();
	QSize sz(rec.width() - 900 , rec.height() - 1500);

	wList2->clear();

	Dog* dp = toUI(d);
	std::string str = dp->toStr();
		
	QListWidgetItem *newItem = new QListWidgetItem;
	
	if (this->ctrl.vectorGetSize() != 0) {
		wList2->addItem(QString::fromStdString(str));
	}
	else {
		wList2->addItem("\n\n             No more dogs to adopt!");
		this->button1->setEnabled(false);
		this->button2->setEnabled(false);
		this->button3->setEnabled(false);
	}
}


std::vector<std::string> getData(std::string item) {


	std::vector<std::string> data;
	std::stringstream stringStream(item);
	std::string line;


	while (std::getline(stringStream, line))
	{
		std::size_t prev = 0, pos;
		while ((pos = line.find_first_of(": ", prev)) != std::string::npos)
		{
			if (pos > prev)
				data.push_back(line.substr(prev, pos - prev));
			prev = pos + 1;
		}
		if (prev < line.length())
			data.push_back(line.substr(prev, std::string::npos));
	}

	return data;
}

//------------------------------------------------------------------------------------------//



void GUI::setButton() {

	QWidget *window = new QWidget;

	this->windows.push_back(window);

	QLabel *label = new QLabel(this);
	label->setText("Save file to: ");

	QPushButton *next = new QPushButton("Next");
	QObject::connect(next, &QPushButton::clicked, this , &GUI::setFile);

	QPushButton *quit = new QPushButton("Cancel");
	QObject::connect(quit, &QPushButton::clicked, this, [this, window]() { window->close(); });

    QRadioButton *c1 = new QRadioButton("Html");
	QRadioButton *c2 = new QRadioButton("Csv");
	
	this->qRadPtr.push_back(c1);
	this->qRadPtr.push_back(c2);

	QFormLayout *layout = new QFormLayout;
	layout->addRow(label);
	layout->addRow(c1);
	layout->addRow(c2);
	layout->addRow(quit, next);
	window->setLayout(layout);
	window->show();

}


void GUI::setFile() {
	
	QWidget* window = this->windows[0];

	QRadioButton* c1 = this->qRadPtr[0];
	QRadioButton* c2 = this->qRadPtr[1];

	this->qRadPtr.clear();
	this->windows.clear();

	bool isC = false;

	window->close(); 

	if (c1->isChecked()) {
		this->ctrl.adoptSetIsHtml(true);
		this->ctrl.adoptSetFileName("list.html");
		choseMode();
		isC = true;
		return;
	}

	if (c2->isChecked()) {
		this->ctrl.adoptSetIsHtml(false);
		this->ctrl.adoptSetFileName("list.csv");
		choseMode();
		isC = true;
		return; 
	}

	if ( isC == false )
		GUI::setButton();

}


void GUI::choseMode() {

	this->qRadPtr.clear();
	this->windows.clear();

	QWidget *window = new QWidget;

	this->windows.push_back(window);

	QLabel *label = new QLabel(this);
	label->setText("Please chose the application mode: ");

	QPushButton *next = new QPushButton("Next");
	QObject::connect(next, &QPushButton::clicked, this , &GUI::setMode);

	QPushButton *quit = new QPushButton("Cancel");
	QObject::connect(quit, &QPushButton::clicked, this, [this, window]() { window->close(); });

    QRadioButton *c1 = new QRadioButton("Administrator");
	QRadioButton *c2 = new QRadioButton("User");
	
	this->qRadPtr.push_back(c1);
	this->qRadPtr.push_back(c2);

	QFormLayout *layout = new QFormLayout;

	layout->addRow(label);
	layout->addRow(c1);
	layout->addRow(c2);
	layout->addRow(quit, next);
	window->setLayout(layout);
	window->show();

}

void GUI::setMode() {

	
	QWidget* window = this->windows[0];

	QRadioButton* c1 = this->qRadPtr[0];
	QRadioButton* c2 = this->qRadPtr[1];

	this->qRadPtr.clear();
	this->windows.clear();

	bool isC = false;

	window->close(); 

	if (c1->isChecked()) {
		adminMode();
		isC = true;
	}

	if (c2->isChecked()) {
		userMode();
		isC = true;
	}

	if ( isC == false )
		GUI::choseMode();


}

/// =====================================================================================================

	///			ADMIN MODE 

/// =====================================================================================================


void GUI::adminMode() {

	try {

		QWidget *window = new QWidget;
		QRect rec = QApplication::desktop()->screenGeometry();

		window->resize(rec.width() - 1200, rec.height() - 300);
		wList1->resize(rec.width() - 1200, rec.height());

		refresh(this->ctrl.controllerGetDogs());

		QPushButton *Add = new QPushButton("Add");
		QObject::connect(Add, &QPushButton::clicked, this, &GUI::add);

		QPushButton *Remove = new QPushButton("Remove");
		QObject::connect(Remove, &QPushButton::clicked, this, [this, window]() {
			try{	
				if (this->wList1->selectedItems().size() == 0) {
					throw RepoException{ "Error: No item selected!" };
				}
	
				QString val = wList1->currentItem()->text();
				std::string std = val.toStdString();

				std::vector<std::string> data = getData(std);

				if (data[2] != "Name") {
					data[1] += " " + data[2];
				}

				if (data[3] == "Name") {
					data[3] = data[4];
				}

		
					this->ctrl.removeDogFromRepository(data[1], data[3]);
					refresh(this->ctrl.controllerGetDogs());
			}
			catch (RepoException& r) {
				QMessageBox messageBox;
				messageBox.critical(0,"Error", r.what());
				messageBox.setFixedSize(500,200);
			}

			catch (ValidateException& v) {
				QMessageBox messageBox;
				messageBox.critical(0,"Error", v.what());
				messageBox.setFixedSize(500,200);
			}
		});

		QPushButton *Update = new QPushButton("Update");
		QObject::connect(Update, &QPushButton::clicked, this, [this, window]() { choseUpdate();  });

		QPushButton *Filter = new QPushButton("Filter");
		QObject::connect(Filter, &QPushButton::clicked, this, [this, window]() {

			QWidget* w2 = new QWidget;

			QLabel* t = new QLabel;
			t->setText("Please enter the weight: ");

			QLabel* we = new QLabel;

			we->setText("Weight: ");

			QLineEdit* br1 = new QLineEdit;
			QLineEdit* we1 = new QLineEdit;


			QPushButton *Back = new QPushButton("Cancel");
			QObject::connect(Back, &QPushButton::clicked, this, [this, w2]() { w2->close(); });

			QPushButton *Exit = new QPushButton("Submit");
			QObject::connect(Exit, &QPushButton::clicked, this, [this, w2, br1, we1]() { w2->close();

			QString qb = br1->text();
			QString qw = we1->text();

			std::string breed = qb.toStdString();
			int weight = qw.toInt();

			Validate::validateInt(std::to_string(weight));

			QWidget* w3 = new QWidget;

			QRect rec = QApplication::desktop()->screenGeometry();
			QSize sz(rec.width() - 900, rec.height() - 900);

			QListWidget* lst = new QListWidget(w3);

			std::vector<Dog> d;

			try {
				d = this->ctrl.filterDogs(weight);
			}
			catch (RepoException& r) {
				QMessageBox messageBox;
				messageBox.critical(0,"Error", r.what());
				messageBox.setFixedSize(500,200);
				return;
			}
			
			for (int i = 0; i < d.size(); i++) {
				Dog* dp = toUI(d[i]);
				std::string str = dp->toStr();

				QListWidgetItem *newItem = new QListWidgetItem;
				newItem->setText(QString::fromStdString(str));
				newItem->setSizeHint(sz);
				lst->insertItem(i, newItem);
			}

			QFormLayout *l = new QFormLayout;
			l->addRow(lst);

			w3->setLayout(l);
			w3->show();

			});

			QFormLayout* f = new QFormLayout;
			f->addRow(t);
			f->addRow(we, we1);
			f->addRow(Back, Exit);

			w2->setLayout(f);
			w2->show();

		});

		QPushButton *Back = new QPushButton("Back to mode select");
		QObject::connect(Back, &QPushButton::clicked, this, [this, window]() { window->close(); choseMode(); });

		QPushButton *Exit = new QPushButton("Exit");
		QObject::connect(Exit, &QPushButton::clicked, this, [this, window]() { window->close(); });


		QVBoxLayout* layout = new QVBoxLayout;
		QFormLayout* l2 = new QFormLayout;

		l2->addRow(Back, Exit);

		layout->addWidget(wList1);
		layout->addWidget(Add);
		layout->addWidget(Update);
		layout->addWidget(Remove);
		layout->addWidget(Filter);
		layout->addLayout(l2);

		window->setLayout(layout);
		window->show();
	}
	catch (RepoException& r) {
		QMessageBox messageBox;
		messageBox.critical(0,"Error", r.what());
		messageBox.setFixedSize(500,200);
	}

	catch (ValidateException& v) {
		QMessageBox messageBox;
		messageBox.critical(0,"Error", v.what());
		messageBox.setFixedSize(500,200);
	}
}


void GUI::add() {

	QWidget* window = new QWidget;

	QLabel *label = new QLabel;
	label->setText("Please enter the requiered data: ");

	QLabel* b = new QLabel;
	QLabel* n = new QLabel;
	QLabel* a = new QLabel;
	QLabel* w = new QLabel;
	QLabel* l = new QLabel;

	b->setText("Breed: ");
	n->setText("Name: ");
	a->setText("Age: ");
	w->setText("Weight: ");
	l->setText("Link: ");

	QLineEdit* b1 = new QLineEdit;
	QLineEdit* n1 = new QLineEdit;
	QLineEdit* a1 = new QLineEdit;
	QLineEdit* w1 = new QLineEdit;
	QLineEdit* l1 = new QLineEdit;

	
	QPushButton *Back = new QPushButton("Cancel");
	QObject::connect(Back, &QPushButton::clicked, this, [this, window]() { window->close();});
	
	QPushButton *Exit = new QPushButton("Submit");
	QObject::connect(Exit, &QPushButton::clicked, this, [this, window, b1, n1, a1, w1, l1]() { window->close(); 
	
		QString s1 = b1->text();
		QString s2 = n1->text();
		QString s3 = a1->text();
		QString s4 = w1->text();
		QString s5 = l1->text();

		std::string breed = s1.toStdString();
		std::string name = s2.toStdString();
		int age = s3.toInt();
		int weight = s4.toInt();
		std::string photo = s5.toStdString();

		try {

			this->ctrl.addDogToRepository(breed, name, age, weight, photo);
			this->ctrl.adoptSetVector(this->ctrl.controllerGetDogs());
		}
		catch (RepoException& r) {
			QMessageBox messageBox;
			messageBox.critical(0,"Error", r.what());
			messageBox.setFixedSize(500,200);
		}
		catch (ValidateException& v) {
			QMessageBox messageBox;
			messageBox.critical(0,"Error", v.what());
			messageBox.setFixedSize(500,200);
		}

		
		refresh(this->ctrl.controllerGetDogs());
	});

	QFormLayout* lay = new QFormLayout;

	lay->addRow(label);
	lay->addRow(b, b1);
	lay->addRow(n, n1);
	lay->addRow(a, a1);
	lay->addRow(w, w1);
	lay->addRow(l, l1);
	lay->addRow(Back, Exit);

	window->setLayout(lay);
	window->show();

}

void GUI::choseUpdate() {

	this->qRadPtr.clear();
	this->windows.clear();

	QWidget *window = new QWidget;

	this->windows.push_back(window);

	QLabel *label = new QLabel(this);
	label->setText("Please chose what need updating: ");

	QPushButton *next = new QPushButton("Submit");
	QObject::connect(next, &QPushButton::clicked, this, [this, window]() { window->close(), update(); });

	QPushButton *quit = new QPushButton("Cancel");
	QObject::connect(quit, &QPushButton::clicked, this, [this, window]() { window->close(); });

    QRadioButton *c1 = new QRadioButton("Breed");
	QRadioButton *c2 = new QRadioButton("Name");
	QRadioButton *c3 = new QRadioButton("Age");
	QRadioButton *c4 = new QRadioButton("Photo");
	
	this->qRadPtr.push_back(c1);
	this->qRadPtr.push_back(c2);
	this->qRadPtr.push_back(c3);
	this->qRadPtr.push_back(c4);

	QFormLayout *layout = new QFormLayout;

	layout->addRow(label);
	layout->addRow(c1);
	layout->addRow(c2);
	layout->addRow(c3);
	layout->addRow(c4);
	layout->addRow(quit, next);
	window->setLayout(layout);
	window->show();
}


void GUI::update() {

	
	QRadioButton* c1 = this->qRadPtr[0];
	QRadioButton* c2 = this->qRadPtr[1];
	QRadioButton* c3 = this->qRadPtr[2];
	QRadioButton* c4 = this->qRadPtr[3];

	this->qRadPtr.clear();
	this->windows.clear();

	
	try{
		if (this->wList1->selectedItems().size() == 0) {
			throw RepoException{ "Error: No item selected!" };
			
		}
	}
	
	catch(RepoException& r) {
		QMessageBox messageBox;
		messageBox.critical(0,"Error", r.what());
		messageBox.setFixedSize(500,200);
		return;
	}

	QString val = wList1->currentItem()->text();
	std::string std = val.toStdString();
	
	std::vector<std::string> data = getData(std);

	if (data[2] != "Name") {
		data[1] += " " + data[2];
	}

	if (data[3] == "Name") {
		data[3] = data[4];
	}

	bool isC = false;

	if (c1->isChecked()) {
		isC = true;

		QWidget* window = new QWidget;
		QLabel* t = new QLabel;
		t->setText("Please enter the new breed: ");
		QLabel* l = new QLabel;
		l->setText("New Value");
		QLineEdit* e = new QLineEdit;

		
		QPushButton *Back = new QPushButton("Cancel");
		QObject::connect(Back, &QPushButton::clicked, this, [this, window]() { window->close();});
	
		QPushButton *Exit = new QPushButton("Submit");
		QObject::connect(Exit, &QPushButton::clicked, this, [this, window, e, data]() { window->close(); 
		
			QString qstr = e->text();
			std::string str = qstr.toStdString();

			try{
				if (str == "") 
					throw RepoException{ "Error: No value entered!" };
			}
	
			catch(RepoException& r) {
				QMessageBox messageBox;
				messageBox.critical(0,"Error", r.what());
				messageBox.setFixedSize(500,200);
				return;
			}

			try {
				this->ctrl.updateDogBreed(data[1], data[3], str);
			}
			catch (RepoException& r) {
				QMessageBox messageBox;
				messageBox.critical(0,"Error", r.what());
				messageBox.setFixedSize(500,200);
			}
			catch (ValidateException& v) {
				QMessageBox messageBox;
				messageBox.critical(0,"Error", v.what());
				messageBox.setFixedSize(500,200);
			}
			
			
			refresh(this->ctrl.controllerGetDogs());
			return;
		});
	
		QFormLayout* f = new QFormLayout;
		f->addRow(t);
		f->addRow(l, e);
		f->addRow(Back, Exit);
		window->setLayout(f);
		window->show();

	}

	if (c2->isChecked()) {
		isC = true;

		QWidget* window = new QWidget;
		QLabel* t = new QLabel;
		t->setText("Please enter the new name: ");
		QLabel* l = new QLabel;
		l->setText("New Value");
		QLineEdit* e = new QLineEdit;

		
		QPushButton *Back = new QPushButton("Cancel");
		QObject::connect(Back, &QPushButton::clicked, this, [this, window]() { window->close();});
	
		QPushButton *Exit = new QPushButton("Submit");
		QObject::connect(Exit, &QPushButton::clicked, this, [this, window, e, data]() { window->close(); 
		
			QString qstr = e->text();
			std::string str = qstr.toStdString();

			try{
				if (str == "") 
					throw RepoException{ "Error: No value entered!" };
			}
	
			catch(RepoException& r) {
				QMessageBox messageBox;
				messageBox.critical(0,"Error", r.what());
				messageBox.setFixedSize(500,200);
				return;
			}

			try {
				this->ctrl.updateDogName(data[1], data[3], str);
			}
			catch (RepoException& r) {
				QMessageBox messageBox;
				messageBox.critical(0,"Error", r.what());
				messageBox.setFixedSize(500,200);
			}
			catch (ValidateException& v) {
				QMessageBox messageBox;
				messageBox.critical(0,"Error", v.what());
				messageBox.setFixedSize(500,200);
			}

			refresh(this->ctrl.controllerGetDogs());
			return;
		});
	
		QFormLayout* f = new QFormLayout;
		f->addRow(t);
		f->addRow(l, e);
		f->addRow(Back, Exit);
		window->setLayout(f);
		window->show();
	}

	
	if (c3->isChecked()) {
		isC = true;

		QWidget* window = new QWidget;
		QLabel* t = new QLabel;
		t->setText("Please enter the new age: ");
		QLabel* l = new QLabel;
		l->setText("New Value");
		QLineEdit* e = new QLineEdit;

		
		QPushButton *Back = new QPushButton("Cancel");
		QObject::connect(Back, &QPushButton::clicked, this, [this, window]() { window->close();});
	
		QPushButton *Exit = new QPushButton("Submit");
		QObject::connect(Exit, &QPushButton::clicked, this, [this, window, e, data]() { window->close(); 
		
			QString qstr = e->text();
			
			try {
				int age = qstr.toInt();
				if (age == 0) {
					throw RepoException {"Error: no value\invalid value enterd!"};
				}

				this->ctrl.updateDogAge(data[1], data[3], age);
			}
			catch (RepoException& r) {
				QMessageBox messageBox;
				messageBox.critical(0,"Error", r.what());
				messageBox.setFixedSize(500,200);
			}
			catch (ValidateException& v) {
				QMessageBox messageBox;
				messageBox.critical(0,"Error", v.what());
				messageBox.setFixedSize(500,200);
			}
			refresh(this->ctrl.controllerGetDogs());
			return;
		});
	
		QFormLayout* f = new QFormLayout;
		f->addRow(t);
		f->addRow(l, e);
		f->addRow(Back, Exit);
		window->setLayout(f);
		window->show();

	}

	
	if (c4->isChecked()) {
		
		isC = true;

		QWidget* window = new QWidget;
		QLabel* t = new QLabel;
		t->setText("Please enter the new photo link: ");
		QLabel* l = new QLabel;
		l->setText("New Value");
		QLineEdit* e = new QLineEdit;

		
		QPushButton *Back = new QPushButton("Cancel");
		QObject::connect(Back, &QPushButton::clicked, this, [this, window]() { window->close();});
	
		QPushButton *Exit = new QPushButton("Submit");
		QObject::connect(Exit, &QPushButton::clicked, this, [this, window, e, data]() { window->close(); 
		
			QString qstr = e->text();
			std::string str = qstr.toStdString();
			
			try {
				this->ctrl.updateDogPhoto(data[1], data[3], str);
			}
			catch (RepoException& r) {
				QMessageBox messageBox;
				messageBox.critical(0,"Error", r.what());
				messageBox.setFixedSize(500,200);
			}
			catch (ValidateException& v) {
				QMessageBox messageBox;
				messageBox.critical(0,"Error", v.what());
				messageBox.setFixedSize(500,200);
			}


			refresh(this->ctrl.controllerGetDogs());
			return; 

		});
	
		QFormLayout* f = new QFormLayout;
		f->addRow(t);
		f->addRow(l, e);
		f->addRow(Back, Exit);
		window->setLayout(f);
		window->show();


	}

	if ( isC == false )
		GUI::choseUpdate();

}



/// =====================================================================================================

	///			USER MODE 

/// =====================================================================================================


void GUI::userMode() {

	try {

		QWidget *window = new QWidget;
		QRect rec = QApplication::desktop()->screenGeometry();
		Dog currentDog;

		this->ctrl.adoptResetCuret();
		
		if (this->ctrl.vectorGetSize() != 0) {
			currentDog = this->ctrl.adoptGetCurentDog();
		}
		else {
			QMessageBox::StandardButton reply;
			reply = QMessageBox::question(0, "No dogs avalailable", "There are no dogs out for adoption at the moment \nDo you whish to see the adoption list?", QMessageBox::No|QMessageBox::Yes);
			
			if (reply == QMessageBox::Yes) {
				this->ctrl.adoptOpenAdoptList();
			}

			window->close();
			choseMode();
			return;
		}

		window->resize(rec.width() - 1200, rec.height() - 700);
		wList2->resize(rec.width() - 1200, rec.height() - 700);

		if (this->ctrl.vectorGetSize() != 0) {
			refreshNext(currentDog);
		}

		QPushButton *Open = new QPushButton("View photo");
		QObject::connect(Open, &QPushButton::clicked, this, [this, currentDog]() { this->ctrl.openPhoto(); });

		this->button3 = Open;

		QPushButton *Next = new QPushButton("Next");
		QObject::connect(Next, &QPushButton::clicked, this, [this]() { this->ctrl.adoptNext(); refreshNext(this->ctrl.adoptGetCurentDog()); });

		this->button1 = Next;

		QPushButton *Adopt = new QPushButton("Adopt");
		QObject::connect(Adopt, &QPushButton::clicked, this, [this, Next]() {
			this->ctrl.adoptAdopt(); 
			if (this->ctrl.getRepoLength() == 1)
				this->ctrl.adoptResetCuret(); 
			if (this->ctrl.vectorGetSize() == 0) {
				Next->setEnabled(false);
			}
			refreshNext(this->ctrl.adoptGetCurentDog()); 
		});

		this->button2 = Adopt;

		QPushButton *AdoptList = new QPushButton("View the adoption list");
		QObject::connect(AdoptList, &QPushButton::clicked, this, [this, window]() { this->ctrl.adoptOpenAdoptList(); });

		QPushButton *Filter = new QPushButton("Normal");
		QObject::connect(Filter, &QPushButton::clicked, this, [this, window]() { this->ctrl.adoptSetVector(this->ctrl.controllerGetDogs()); this->ctrl.adoptResetCuret(); refreshNext(this->ctrl.adoptGetCurentDog()); });

		QPushButton *Normal = new QPushButton("Filter");
		QObject::connect(Normal, &QPushButton::clicked, this, [this, window]() {


			QWidget* w2 = new QWidget;

			QLabel* t = new QLabel;
			t->setText("Please enter the weight: ");

			QLabel* ag = new QLabel;
			QLabel* br = new QLabel;

			ag->setText("Age: ");
			br->setText("Breed: ");

			QLineEdit* br1 = new QLineEdit;
			QLineEdit* ag1 = new QLineEdit;


			QPushButton *Back = new QPushButton("Cancel");
			QObject::connect(Back, &QPushButton::clicked, this, [this, w2]() { w2->close(); });

			QPushButton *Exit = new QPushButton("Submit");
			QObject::connect(Exit, &QPushButton::clicked, this, [this, w2, br1, ag1]() { w2->close();

				QString qb = br1->text();
				QString qa = ag1->text();

				std::string breed = qb.toStdString();
				int age = qa.toInt();

				try {
					std::vector<Dog> d = this->ctrl.adoptFilterDogs(breed, age);
					this->ctrl.adoptSetVector(d);
					this->ctrl.adoptResetCuret();

					}
				
				catch (RepoException& r) {
					QMessageBox messageBox;
					messageBox.critical(0,"Error", r.what());
					messageBox.setFixedSize(500,200);
					}

				catch (ValidateException& v) {
					QMessageBox messageBox;
					messageBox.critical(0,"Error", v.what());
					messageBox.setFixedSize(500,200);
					}

				refreshNext(this->ctrl.adoptGetCurentDog());

			});

			QFormLayout* f = new QFormLayout;
			f->addRow(t);
			f->addRow(br, br1);
			f->addRow(ag, ag1);
			f->addRow(Back, Exit);

			w2->setLayout(f);
			w2->show();


		});

		
		QPushButton *Back = new QPushButton("Back to mode select");
		QObject::connect(Back, &QPushButton::clicked, this, [this, window]() { window->close(); choseMode(); });

		QPushButton *Exit = new QPushButton("Exit");
		QObject::connect(Exit, &QPushButton::clicked, this, [this, window]() { window->close(); });


		QVBoxLayout* layout = new QVBoxLayout;
		QFormLayout* l2 = new QFormLayout;

		Open->resize(Back->width(), Open->height());
		Filter->resize(Back->width(), Filter->height());

		l2->addRow(Open, Next);
		l2->addRow(Filter, Normal);
		l2->addRow(Back, Exit);

		layout->addWidget(wList2);
		layout->addWidget(Adopt);
		layout->addWidget(AdoptList);
		layout->addLayout(l2);

		window->setLayout(layout);
		window->show();
	}
	catch (RepoException& r) {
		QMessageBox messageBox;
		messageBox.critical(0,"Error", r.what());
		messageBox.setFixedSize(500,200);
	}

	catch (ValidateException& v) {
		QMessageBox messageBox;
		messageBox.critical(0,"Error", v.what());
		messageBox.setFixedSize(500,200);
	}
}