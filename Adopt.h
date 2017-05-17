#pragma once
#include <vector>
#include <algorithm>
#include "Domain.h"

class AdoptList {

private:
	std::vector<Dog> dogs;
	std::vector<Dog> adoptList;
	std::string fileName;
	bool isHtml;
	int curent = 0;

public:

	//Default constructor
	AdoptList() {};
	
	AdoptList(std::string fileName) { this->fileName = fileName; }

	AdoptList(bool isHtml) {

		this->isHtml = isHtml;

		if (isHtml == true)
			this->fileName = "list.html";
		else
			this->fileName = "list.csv";
	}

	~AdoptList() {}

	void saveHtml();

	void saveCsv();

	void save();

	//Setter for the dynamic vector
	void setVector(std::vector<Dog>& newVector) { this->dogs.resize(newVector.size());  this->dogs = newVector; }

	std::vector<Dog> getDogs() { return this->dogs; }

	std::vector<Dog> getAdoptList() { return this->adoptList; }

	void resetCurent() { this->curent = 0; };

	//Getter for the curent pos
	int getCurentPos() { return this->curent; }

	//Getter for the vector size
	int getVectorSize() { return this->dogs.size(); }

	int getAdoptSize() { return this->adoptList.size(); }

	//Getter for the curent dog
	Dog getCurentDog();

	//Getter for a dog in the vector
	Dog getDogOnPos(int pos) { return this->dogs[pos]; }

	//Getter for a dog in the adoptList
	Dog adoptGetDogOnPos(int pos) { return this->adoptList[pos]; }

	//Adds a dog to the adoption list
	void adoptDog() { this->adoptList.push_back(getDogOnPos(this->getCurentPos())); this->save(); }

	//Removes the adopted dog
	void removeAdoptedDog() { this->dogs.erase(this->dogs.begin() + this->getCurentPos()); }
	
	//Iterates through the dog list
	void next();

	void addDogToVector(Dog& d) { this->dogs.push_back(d); }

	//Opens link to dog photo
	void openPhoto();

	void openAdoptList();
	
	void setIsHtml(bool isHtml) { this->isHtml = isHtml; }

	void setFileName(std::string fileName) { this->fileName = fileName; }

	//Filters by breed and age
	std::vector<Dog> filterDogs(std::string breed, int age);

};

void testAdopt();
