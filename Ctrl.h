#pragma once
#include "Repository.h"
#include "Adopt.h"
#include "Validator.h"

class Controller
{
private:
	Repository repo;
	AdoptList adopt;

public:
	Controller(const Repository& r, const AdoptList& a);

	~Controller() {}

	Repository getRepo() const { return repo; }

	std::vector<Dog> controllerGetDogs() { return repo.getDogs(); }

	std::vector<Dog>::iterator getStart() { return this->repo.getStart(); };
	std::vector<Dog>::iterator getEnd() { return this->repo.getEnd(); };

	std::vector<Dog>::iterator getPos(const std::string& breed, const std::string& name) { return this->repo.search(breed, name); }

	// Adds a song with the given data to the song repository.
	int addDogToRepository(const std::string& breed, const std::string& name, int age, int weight, const std::string& photo);

	// Adds all the songs from the repository, that have the given artist, to the current playlist.
	int removeDogFromRepository(const std::string& breed, const std::string& name);

	int updateDogBreed(const std::string& breed, const std::string& name, const std::string& newBreed);

	int updateDogName(const std::string& breed, const std::string& name, const std::string& newName);

	int updateDogAge(const std::string& breed, const std::string& name, const int Age);

	int updateDogPhoto(const std::string& breed, const std::string& name, const std::string& Photo);

	int getRepoLength() const { return repo.getSize(); };

	Dog controllerGetDogOnPos(int pos) { return repo.getDogOnPos(pos); }

	std::vector<Dog> Controller::filterDogs(int weight);
	//Adopt management

	Dog adoptGetCurentDog();

	void adoptNext();

	void adoptAdopt();

	void adoptRemoveAdopted();

	void openPhoto();

	void adoptResetCuret() { this->adopt.resetCurent();  };

	std::vector<Dog> adoptFilterDogs(std::string& breed, int age) {
		
		Validate::validateInt(std::to_string(age));
		return this->adopt.filterDogs(breed, age);
	
	};

	
	std::vector<Dog> getAdoptionList() { return this->adopt.getAdoptList(); };

	void adoptSetVector(std::vector<Dog>& newVector) { this->adopt.setVector(newVector); }

	void adoptOpenAdoptList() { this->adopt.openAdoptList(); }

	void adoptSetIsHtml(bool isHtml) { this->adopt.setIsHtml(isHtml); }

	void adoptSetFileName(std::string fileName) { this->adopt.setFileName(fileName); }

	int adoptGetSize() { return this->adopt.getAdoptSize(); };
	int vectorGetSize() { return this->adopt.getVectorSize(); };
};

void testController();