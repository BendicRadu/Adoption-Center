#include "UI.h"
#include "Exceptions.h"
#include "Validator.h"

using namespace std;

void printDog(Dog d) {
	
	Dog* uiDisp = new UiDog{ d.getBreed(), d.getName(), d.getAge(), d.getWeight(), d.getPhoto() };
	cout << uiDisp->toStr();
}

void UI::printMenu(){
	
	cout << endl;
	cout << "1 - Manage dog repository." << endl;
	cout << "2 - Manage the adoption list." << endl;
	cout << "0 - Exit" << endl;
}

void UI::printRepositoryMenu(){

	cout << endl;
	cout << "Possible commands: " << endl;
	cout << "1 - Add dog." << endl;
	cout << "2 - Remove dog." << endl;
	cout << "3 - Update dog." << endl;
	cout << "4 - Display all." << endl;
	cout << "5 - Display filtered list." << endl;
	cout << "0 - Exit" << endl;
}

void UI::printAdoptMenu() {

	cout << endl;
	cout << "Possible commands: " << endl;
	cout << "1 - See all dogs." << endl;
	cout << "2 - See dogs from given breed." << endl;
	cout << "3 - See the adoption list." << endl;
	cout << "4 - See html/csv adoption list." << endl;
	cout << "0 - Exit." << endl;

}

void UI::printSaveMenu() {

	cout << endl;
	cout << "In which type of file should be the adoption list sored?" << endl;
	cout << "1 - Html." << endl;
	cout << "2 - Csv. " << endl;
	cout << "3 - Exit. " << endl;
}

void UI::printUpdateMenu() {
	cout << endl;
	cout << "Possible updated: " << endl;
	cout << "1 - Breed." << endl;
	cout << "2 - Name." << endl;
	cout << "3 - Age." << endl;
	cout << "4 - Photo." << endl;
	cout << "0 - Exit." << endl;
}


void printDogMenu() {

	cout << endl;
	cout << "1 - Adopt." << endl;
	cout << "2 - View Photo." << endl;
	cout << "3 - Next." << endl;
	cout << "0 - Exit." << endl;

}


void UI::readIdentifiers(std::string& breed, std::string& name) {
	cout << endl;
	cout << "Enter the breed: ";
	getline(cin, breed);
	cout << "Enter the name: ";
	getline(cin, name);
}

void UI::readFilter(std::string& breed, int& age) {
	
	cout << endl;
	cout << "Enter the breed: ";
	getline(cin, breed);
	cout << "Enter the maximum age: ";
	cin >> age;
}

void UI::uiAddDogToRepo()
{
	cout << endl;
	cout << "Enter the breed: ";
	std::string breed;
	getline(cin, breed);
	cout << "Enter the name: ";
	std::string name;
	getline(cin, name);
	int age = 0;
	cout << "Enter the age: ";
	cin >> age;

	int weight = 0;
	cout << "Enter the weight: ";
	cin >> weight;

	if (cin.fail()) {
		cout << "\nInvalid age\n";
		return;
	}
	cout << "Photo link: ";
	std::string photo;
	cin >> photo;
	
	if (this->ctrl.addDogToRepository(breed, name, age, weight, photo))
		cout << "\nDog added\n";
	else
		cout << "\nDog was not added\n";
}

void UI::uiRemoveDogFromRepo() {
	std::string breed, name;
	readIdentifiers(breed, name);
	if (this->ctrl.removeDogFromRepository(breed, name))
		cout << "\nDog was removed\n";
	else
		cout << "\nDog was not removed\n";
}


void UI::uiUpdateBreed() {
	std::string breed, name, newBreed;
	readIdentifiers(breed, name);
	cout << "Enter the new breed: ";
	getline(cin, newBreed);
	if (this->ctrl.updateDogBreed(breed, name, newBreed))
		cout << "\nDog updated\n";
	else
		cout << "\nUpdate failed\n";
}

void UI::uiUpdateName() {
	std::string breed, name, newName;
	readIdentifiers(breed, name);
	cout << "Enter the new name: ";
	getline(cin, newName);
	if(this->ctrl.updateDogName(breed, name, newName))
		cout << "\nDog updated\n";
	else
		cout << "\n\nUpdate failed\n\n";
}

void UI::uiUpdateAge() {
	std::string breed, name;
	int newAge;
	readIdentifiers(breed, name);
	cout << "Enter the new age:  \n";
	cin >> newAge;
	cin.ignore();
	if(this->ctrl.updateDogAge(breed, name, newAge))
		cout << "\n\nDog updated\n\n";
	else
		cout << "\n\nUpdate failed\n\n";
}

void UI::uiUpdatePhoto() {
	std::string breed, name, newPhoto;
	readIdentifiers(breed, name);
	cout << "Enter the new photo: ";
	getline(cin, newPhoto);
	this->ctrl.updateDogPhoto(breed, name, newPhoto);
}

void UI::update() {

	int opt = 0;
	printUpdateMenu();
	cout << "\n Enter your choice: ";
	cin >> opt;
	cin.ignore();
	
	switch (opt)
	{
		default:
			break;

		case 1: 
			uiUpdateBreed(); 
			break;
		

		case 2: 
			uiUpdateName(); 
			break;
		

		case 3: 
			uiUpdateAge(); 
			break;
		

		case 4:
			 uiUpdatePhoto();
			 break;
		
	
		case 5:
			return;
	}
	
}

Dog* toUiDog(Dog d) { return  new UiDog{ d.getBreed(), d.getName(), d.getAge(), d.getWeight(), d.getPhoto() }; }
std::string toUiStr(Dog* d) { return d->toStr(); }

void UI::displayAllDogsRepo()
{
	std::vector<Dog> v = this->ctrl.controllerGetDogs();
	Dog *dogs = v.data();

	if (dogs == NULL)
		return;

	if (v.size() == 0)
	{
		cout << "\nThere are no dogs in the repository.\n" << endl;
		return;
	}

	std::vector<Dog*> uiV;
	uiV.resize(v.size());
	std::transform(v.begin(), v.end(), uiV.begin(), toUiDog);

	std::vector<std::string> disp;
	disp.resize(v.size());
	std::transform(uiV.begin(), uiV.end(), disp.begin(), toUiStr);
	
	std::ostream_iterator<std::string> output_iterator(cout);
    std::copy(disp.begin(), disp.end(), output_iterator);
}

void UI::displayFilteredDogs(int weight) {

	std::vector<Dog> v = this->ctrl.filterDogs(weight);
	Dog *dogs = v.data();
	if (dogs == NULL)
		return;

	if (v.size() == 0){
		cout << "\nThere are no dogs in the repository.\n" << endl;
		return;
	}

	std::ostream_iterator<Dog> output_iterator(cout);
    std::copy(v.begin(), v.end(), output_iterator);
}

void UI::displayAdoptionList() {
	
	std::vector<Dog> v = this->ctrl.getAdoptionList();
	Dog *dogs = v.data();
	if (dogs == NULL)
		return;
	if (v.size() == 0)
	{
		cout << "\n No dogs adopted :( .\n" << endl;
		return;
	}

	std::ostream_iterator<Dog> output_iterator(cout);
    std::copy(v.begin(), v.end(), output_iterator);

}

void UI::uiAdoptNext(std::vector<Dog>& dyn) {
	
	this->ctrl.adoptSetVector(dyn);

	while (true) {
		Dog d = this->ctrl.adoptGetCurentDog();

		if (d.getBreed() == "None") {
			cout << "\nNo more dogs are available adoption\n";
			return;
		}
		else
			printDog(d);

		printDogMenu();

		int adoptOpt;

		cout << "Enter your option: ";
		cin >> adoptOpt;

		switch (adoptOpt)
		{

		case 1:
			this->ctrl.adoptAdopt();
			if (this->ctrl.getRepoLength() == 1)
				this->ctrl.adoptResetCuret();
			cout << "\nCongratulations! You are now a pet owner!\n";
			this->ctrl.adoptRemoveAdopted();
			break;

		case 2:
			this->ctrl.openPhoto();
			break;

		case 3:
			this->ctrl.adoptNext();
			break;

		case 0:
			return;

		default:
			break;
		}
	}
}

void UI::run()
{

	
	bool isVal = false;

	while (!isVal) {

		UI::printSaveMenu();
		int commandSave{ 0 };
		cout << "Input the command: ";
		cin >> commandSave;
		cin.ignore();
		
		switch (commandSave) {

		case 3:
			return;

		case 1: {
			this->ctrl.adoptSetIsHtml(true);
			this->ctrl.adoptSetFileName("list.html");
			isVal = true;
			break;
		}

		case 2: {
			this->ctrl.adoptSetIsHtml(false);
			this->ctrl.adoptSetFileName("list.csv");
			isVal = true;
			break;
		}
		default:
			cout << "\nInvalid Input\n";
		}
	}

	while (true)
	{
		UI::printMenu();
		int command{ 0 };
		cout << "Input the command: ";
		cin >> command;
		cin.ignore();
		if (command == 0)
			break;

		// repository management
		if (command == 1)
		{
			while (true)
			{
				UI::printRepositoryMenu();
				int commandRepo{ 0 };
				cout << "Input the command: ";
				cin >> commandRepo;
				cin.ignore();
				if (commandRepo == 0)
					break;
				switch (commandRepo)
				{
				case 1:
					try {
						this->uiAddDogToRepo();
						break;
					}

					catch (ValidateException& v) {
						cout << v.what() << endl;
						break;
					}

					catch (RepoException& r) {
						cout << r.what() << endl;
						break;
					}

				case 2:
					try {
						this->uiRemoveDogFromRepo();
						break;
					}

					catch (RepoException& r) {
						cout << r.what() << endl;
						break;
					}

				case 3:
					try {
						this->update();
						break;
					}

					catch (RepoException& r) {
						cout << r.what() << endl;
						break;
					}

				case 4:
					this->displayAllDogsRepo();
					break;

				case 5: {

					int weight;
					cout << "\nEnter weight: ";

					try {
						cin >> weight;
						Validate::validateInt(to_string(weight));
						this->displayFilteredDogs(weight);
					}
					catch (ValidateException& v) {
						cout << v.what() << endl;
					}

					catch (RepoException& r) {
						cout << r.what() << endl;
					}

				}

				case 0:
					break;

				default:
					cout << "\nInvalid input\n";

				}
			}
		}

		if (command == 2) {
			while (true) {

				std::string breed;
				int age;
				
				this->ctrl.adoptSetVector(ctrl.controllerGetDogs());

				this->ctrl.adoptResetCuret();

				UI::printAdoptMenu();
				int commandAdopt{ 0 };
				cout << "Input the command: ";
				cin >> commandAdopt;
				cin.ignore();

				if (commandAdopt == 0)
					break;

				switch (commandAdopt)
				{

				case 1: {
					this->ctrl.adoptSetVector(ctrl.controllerGetDogs());
					UI::uiAdoptNext(this->ctrl.controllerGetDogs());
					break;
				}
				case 2: {
					this->ctrl.adoptSetVector(ctrl.controllerGetDogs());
					readFilter(breed, age);
					std::vector<Dog> filter = this->ctrl.adoptFilterDogs(breed, age);
					UI::uiAdoptNext(filter);
					break;
				}
				case 3: {
					this->ctrl.adoptSetVector(ctrl.controllerGetDogs());
					UI::displayAdoptionList();
					break;
				}

				case 4: {
					this->ctrl.adoptOpenAdoptList();
					break;
				}
				default:
					break;
				}

			}
		}

	}
}

