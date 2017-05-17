#include "Ctrl.h"
#include <assert.h>
#include "Validator.h"

Controller::Controller(const Repository& r, const AdoptList& a) {
	this->repo = r;
	this->adopt = a;
}


int Controller::addDogToRepository(const std::string& breed, const std::string& name, int age, int weight, const std::string& photo){
	Dog d{ breed, name, age, weight, photo };
	
	Validate::validate(d);

	if (this->repo.addDog(d) == 1) {
		this->adopt.setVector(controllerGetDogs());
		return 1;
	 }
}

int Controller::removeDogFromRepository(const std::string& breed, const std::string& name) {

	if (this->repo.removeDog(breed, name) == 1) {
		this->adopt.setVector(controllerGetDogs());
		return 1;
	 }
	return 0;
}


int Controller::updateDogBreed(const std::string& breed, const std::string& name, const std::string& newBreed) {
	if (this->repo.updateBreed(breed, name, newBreed) == 1) {
		this->adopt.setVector(controllerGetDogs());
		return 1;
	}
	return 0;
}

int Controller::updateDogName(const std::string& breed, const std::string& name, const std::string& newName) {
	if (this->repo.updateName(breed, name, newName)) {
		this->adopt.setVector(controllerGetDogs());
		return 1;
	}
	return 0;
}

int Controller::updateDogAge(const std::string& breed, const std::string& name, const int newAge) {
	Validate::validateInt(std::to_string(newAge));
	if (this->repo.updateAge(breed, name, newAge)) {
		this->adopt.setVector(controllerGetDogs());
		return 1;
	}
	return 0;
}

int Controller::updateDogPhoto(const std::string& breed, const std::string& name, const std::string& newPhoto) {
	if (this->repo.updatePhoto(breed, name, newPhoto)) {
		this->adopt.setVector(controllerGetDogs());
		return 1;
	}
	return 0;
}

std::vector<Dog> Controller::filterDogs(int weight) {
	Validate::validateInt(std::to_string(weight));
	return this->repo.getDogsUnderWeight(weight);
}

// Adoption list managemet

void Controller::adoptRemoveAdopted() {
	this->adopt.removeAdoptedDog();
}

void Controller::adoptAdopt() {
	Dog d = adoptGetCurentDog();
	this->adopt.adoptDog();
	this->removeDogFromRepository(d.getBreed(), d.getName());
	this->adopt.setVector(this->controllerGetDogs());
}

Dog Controller::adoptGetCurentDog() {
	return this->adopt.getCurentDog();
}

void Controller::adoptNext() {
	this->adopt.next();
}

void Controller::openPhoto() { this->adopt.openPhoto(); }



// Tests 

Controller initControllerTest() {
	Controller test{ Repository {}, AdoptList{} };
	test.addDogToRepository("Breed", "Name", 3, 1, "4");
	std::vector<Dog> vec;
	vec.push_back(Dog{ "Breed", "Name", 3, 1, "4" });
	test.adoptSetVector(vec);
	return test;
}

void testAddToRepo() {
	Controller c = initControllerTest();
	assert(c.getRepoLength() == 1);
}

void testRemoveFromRepo() {
	Controller c = initControllerTest();
	c.removeDogFromRepository("Breed", "Name"); 
	assert(c.getRepoLength() == 0);
}


void testUpdate() {
	Controller c = initControllerTest();
	c.updateDogBreed("1", "2", "N");
	c.updateDogName("N", "2", "Name");
	c.updateDogAge("N", "Name", 10);
	c.updateDogPhoto("N", "Name", "N");

	assert(c.controllerGetDogOnPos(0).getBreed() == "N");

	assert(c.controllerGetDogOnPos(0).getName() == "Name");
	assert(c.controllerGetDogOnPos(0).getAge() == 10);
	assert(c.controllerGetDogOnPos(0).getPhoto() == "N");

}

void testAdoptRemove() {

	Controller c = initControllerTest();
	c.adoptRemoveAdopted();
}

void testCurent() {
	
	Controller c = initControllerTest();
	Dog current = c.adoptGetCurentDog();
	Dog d{"1", "2", 3, 1, "4"};
	assert(d == current);
}

void testAdoptNext(){

	Controller c = initControllerTest();
	Dog current = c.adoptGetCurentDog();
	Dog d{"1", "2", 3, 1, "4"};
	assert(d == current);
	c.adoptNext();
	assert(d == current);

}

void testControllerWeightFilter() {
	
	Controller a = initControllerTest();
	
	Dog d1{ "1", "2", 3, 1, "4" };

	std::vector<Dog> c = a.filterDogs(100);
	Dog d3 = c[0];
	assert(d3 == d1);
}

void testAdoptAdopt() {
	
	Controller c = initControllerTest();
	c.adoptAdopt();
	assert(c.getRepoLength() == 0);

}

void testResetCurrent() {

	Controller c = initControllerTest();
	c.adoptNext();
	c.adoptResetCuret();
	Dog current = c.adoptGetCurentDog();
	Dog d{"1", "2", 3, 1, "4"};
	assert(d == current);
}

void testAdoptFilterDogs() {

	Controller c = initControllerTest();
	std::string breed = "oo";
	std::vector<Dog> fil = c.adoptFilterDogs(breed, 1);
	assert(fil.size() == 0);
}

void testAdoptGetAdoptionList() {

	Controller c = initControllerTest();
	std::string breed = "oo";
	std::vector<Dog> fil = c.getAdoptionList();
	assert(fil.size() == 0);
}

void testController() {
	testAddToRepo();

	testRemoveFromRepo();
	testUpdate();

	testAdoptRemove();
	testCurent();
	testAdoptNext();
	testControllerWeightFilter();
	testAdoptAdopt();
	testResetCurrent();
	testAdoptFilterDogs();
	testAdoptGetAdoptionList();
}


