#pragma once
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include "Domain.h"
#include "Exceptions.h"

class Repository{

private:
	std::vector<Dog> dogs;
	std::string fileName;

public:
	/*
		Default constructor. 
		Initializes an object of type repository.
	*/
	Repository() {}


	//File constructor 
	Repository(const std::string fileName) {
	
		Dog d;
		this->fileName = fileName;
		std::ifstream file(fileName);
		
		while (file.good()) {
			file >> d;
			if (d.isValid())
				this->addDog(d);
		}
		file.close();
	}
	
	~Repository() {}

	//Getter for the file name
	std::string getFileName() { return this->fileName; }

	Dog getDogOnPos(int pos) { return dogs[pos]; }
	
	//Dog* getAllDogs() { return dogs.getAllElems(); };
	
	/*
		Adds a dog to the repository.
		Input: d - Dog.
		Output: the Dog is added to the repository.
	*/
	int addDog(const Dog& d);
	/*
		Removes a dog from the repository.
		Input: pos - position of the elem
		Output: the Dog is removed from the repository.
	*/
	int removeDog(std::string breed, std::string name);
	
	//Updates the breed of the dog
	int updateBreed(const std::string breed, std::string name, std::string newBreed);
	
	//Updates the name of the dog
	int updateName(std::string breed, std::string name, std::string newName);

	//Updates the age of the dog
	int updateAge(const std::string breed, std::string name, int newAge);

	//Update the photo of the dog
	int updatePhoto(const std::string breed, std::string name, std::string newPhoto);
	
	//Return the size of the repo
	int getSize() const { return dogs.size(); };

	//Returns the position of a Dog based on breed and name
	//Returns -1 if not found
	std::vector<Dog>::iterator search(std::string breed, std::string name);

	std::vector<Dog> getDogsUnderWeight(int weight);

	std::vector<Dog>::iterator getStart() { return this->dogs.begin(); };
	std::vector<Dog>::iterator getEnd() { return this->dogs.end(); };

	std::vector<Dog> getDogs() const { return dogs; };

private:
	void save();

};

void testRepo();