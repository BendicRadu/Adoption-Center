#include "Repository.h"
#include <string>
#include <assert.h>

void Repository::save() {

	std::ofstream output_file(this->fileName);
    std::ostream_iterator<Dog> output_iterator(output_file);
    std::copy(this->dogs.begin(), this->dogs.end(), output_iterator);
	output_file.close();
}

std::vector<Dog>::iterator Repository::search(const std::string breed, std::string name) {
	return std::find_if(this->dogs.begin(), this->dogs.end(), [breed, name](Dog d) -> bool {
        if (d.getName() == name && d.getBreed() == breed)
			return true;
        return false;
    });
}

int Repository::addDog(const Dog& d) {

	std::vector<Dog>::iterator pos = Repository::search(d.getBreed(), d.getName());

	if (pos == this->dogs.end()) {
		this->dogs.push_back(d);
		save();
		return 1;
	}
	throw (RepoException("Repository Error: Only unique values can be stored"));
	return 0;
}

int Repository::removeDog(const std::string breed, std::string name) {
	
	std::vector<Dog>::iterator pos = Repository::search(breed, name);
	if (pos != this->dogs.end()) {
		this->dogs.erase(pos);
		save();
		return 1;
	}
	throw (RepoException("Repository Error: Value not found"));
	return 0;
}


int Repository::updateBreed(const std::string breed, std::string name, std::string newBreed) {

	std::vector<Dog>::iterator it = Repository::search(breed, name);
	if (it == this->dogs.end()) {
		throw (RepoException("Repository Error: Only unique values can be stored"));
		return -1;
	}

	std::vector<Dog>::iterator it1 = Repository::search(newBreed, name);
	if (it1 != this->dogs.end()) {
		
		throw (RepoException("Repository Error: Only unique values can be stored"));
		return -1;
	}

	int pos = it - this->dogs.begin();

	this->dogs.data()[pos].setBreed(newBreed);
	save();
	return 1;
}

int Repository::updateName(const std::string breed, std::string name, std::string newName) {

	
	std::vector<Dog>::iterator it = Repository::search(breed, name);
	if (it == this->dogs.end()){
		
		throw (RepoException("Repository Error: Only unique values can be stored"));
		return -1;
	}

	std::vector<Dog>::iterator it1 = Repository::search(breed, newName);
	if (it1 != this->dogs.end()){
		
		throw (RepoException("Repository Error: Only unique values can be stored"));
		return -1;
	}

	int pos = it - this->dogs.begin();

	this->dogs.data()[pos].setName(newName);
	save();
	return 1;
}


int Repository::updateAge(const std::string breed, std::string name, int newAge) {

	
	std::vector<Dog>::iterator it = Repository::search(breed, name);
	if (it == this->dogs.end()){
		
		throw (RepoException("Repository Error: Only unique values can be stored"));
		return -1;
	}
	
	int pos = it - this->dogs.begin();

	this->dogs.data()[pos].setAge(newAge);
	save();
	return 1;
}


int Repository::updatePhoto(const std::string breed, std::string name, std::string newPhoto) {

	std::vector<Dog>::iterator it = Repository::search(breed, name);
	if (it == this->dogs.end()){
		
		throw (RepoException("Repository Error: Only unique values can be stored"));
		return -1;
	}

	int pos = it - this->dogs.begin();

	this->dogs.data()[pos].setPhoto(newPhoto);
	save();
	return 1;
}

std::vector<Dog> Repository::getDogsUnderWeight(int weight) {

	std::vector<Dog> filter (this->dogs.size());
	auto it = std::copy_if(this->dogs.begin(), this->dogs.end(), filter.begin(), [weight](Dog d) { return d < weight; });
	filter.resize(std::distance(filter.begin(), it));

	if (filter.size() == 0) {
		throw (RepoException("Error: No value with specific data found"));
	}

	return filter;
}

//Tests

Repository initTestRepo() {
	Repository a;
	return a;
}


void testRepoAdd() {

	Repository a = initTestRepo();
	Dog d = Dog("1", "1", 1, 1, "1");

	assert(a.getSize() == 0);
	a.addDog(d);
	
	assert(a.getSize() == 1);

	assert(a.getDogOnPos(0).getBreed() == d.getBreed());

	assert(a.getDogOnPos(0).getName() == d.getName());
	assert(a.getDogOnPos(0).getAge() == d.getAge());
	assert(a.getDogOnPos(0).getPhoto() == d.getPhoto());

	try {
		a.addDog(d);
	}
	catch (RepoException) {

	}
	assert(a.getSize() == 1);
	a.removeDog(d.getBreed(), d.getName());
}

void testRepoRemove() {

	Repository a = initTestRepo();
	Dog d = Dog("1", "2", 1, 1, "1");

	assert(a.getSize() == 0);
	a.addDog(d);
	
	assert(a.getSize() == 1);

	assert(a.getDogOnPos(0).getBreed() == d.getBreed());
	assert(a.getDogOnPos(0).getName() == d.getName());
	assert(a.getDogOnPos(0).getAge() == d.getAge());
	assert(a.getDogOnPos(0).getPhoto() == d.getPhoto());
	
	try {
		a.addDog(d);
	}
	catch (RepoException) {

	}
	assert(a.getSize() == 1);

	try {
		a.removeDog(d.getName(), d.getBreed());
	}
	catch (RepoException){}

	assert(a.getSize() == 1);

	a.removeDog(d.getBreed(), d.getName());
	assert(a.getSize() == 0);
}

void testRepoUptade() {
	
	Repository a = initTestRepo();
	Dog d = Dog("1", "2", 1, 1, "1");

	assert(a.getSize() == 0);
	a.addDog(d);
	
	assert(a.getDogOnPos(0).getBreed() == d.getBreed());
	assert(a.getDogOnPos(0).getName() == d.getName());
	assert(a.getDogOnPos(0).getAge() == d.getAge());
	assert(a.getDogOnPos(0).getPhoto() == d.getPhoto());

	a.updateBreed("1", "2", "A");
	a.updateName("A", "2", "B");
	a.updateAge("A", "B", 10);
	a.updatePhoto("A", "B", "C");

	assert(a.getDogOnPos(0).getBreed() == "A");
	assert(a.getDogOnPos(0).getName() == "B");
	assert(a.getDogOnPos(0).getAge() == 10);
	assert(a.getDogOnPos(0).getPhoto() == "C");

	Dog d1{ "2", "B", 1, 1, "1" };
	Dog d2{ "A", "2", 1, 1, "1" };
	a.addDog(d1);
	a.addDog(d2);

	try {
		a.updateBreed("2", "B", "A");
		a.updateName("A", "B", "B");
		a.updateBreed("3", "3", "4");
		a.updateName("3", "3", "4");
		a.updateAge("3", "3", 1);
		a.updatePhoto("3", "3", "4");
		a.updateName("A", "2", "B");
	}
	catch (RepoException){}

	a.removeDog("A", "B");
}


void testWeightFilter() {
	
	Repository a = initTestRepo();
	Dog d1 = Dog("d1", "d2", 4, 50, "1");
	Dog d2 = Dog("1", "2", 1, 1000, "1");
	a.addDog(d1);
	a.addDog(d2);

	std::vector<Dog> c = a.getDogsUnderWeight(100);
	Dog d3 = c[0];
	assert(d3 == d1);
}

void testGetDogs() {
	
	Repository a = initTestRepo();
	Dog d1 = Dog("d1", "d2", 4, 50, "1");
	
	a.addDog(d1);
	std::vector<Dog> c = a.getDogs();
	std::vector<Dog> c1;
	c1.push_back(d1);

	assert(c[0] == c1[0]);

}

void testRepo() {
	testRepoAdd();
	testRepoRemove();
	testRepoUptade();
	testWeightFilter();
	testGetDogs();
}


