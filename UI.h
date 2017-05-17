#pragma once
#include "Ctrl.h"
#include <Windows.h>
#include <string>
#include "outputDog.h"

class UI
{
private:
	Controller& ctrl;

public:
	UI(Controller& c) : ctrl(c) {}

	~UI() {}

	void run();

private:

	static void printMenu();
	static void printRepositoryMenu();
	void displayAllDogsRepo();
	void displayAdoptionList();
	static void printUpdateMenu();
	static void printAdoptMenu();

	void readIdentifiers(std::string& breed, std::string& name);
	void readFilter(std::string& breed, int& age);

	void printSaveMenu();
	void update();

	void uiAddDogToRepo();
	void uiRemoveDogFromRepo();
	void uiUpdateBreed();
	void uiUpdateName();
	void uiUpdateAge();
	void uiUpdatePhoto();
	void displayFilteredDogs(int weight);

	void uiAdoptNext(std::vector<Dog>& dyn);

};
