
#include "Domain.h"
#include <Windows.h>
#include <shellapi.h>
#include <iostream>
#include <string>
#include <assert.h>

Dog::Dog(): breed("None"), name("None"), age(0), photo("None") {}

Dog::Dog(const std::string& breed, const std::string& name, const int& age, const int&weight, const std::string& photo)
{
	this->breed = breed;
	this->name = name;
	this->age = age;
	this->weight = weight;
	this->photo = photo;
}

void Dog::play(){ ShellExecuteA(NULL, NULL, "chrome.exe", this->getPhoto().c_str(), NULL, SW_SHOWMAXIMIZED);}

void Dog::setBreed(std::string newBreed) {
	breed = newBreed;
}

void Dog::setName(std::string newName) {
	name = newName;
}

void Dog::setAge(int newAge) {
	age = newAge;
}

void Dog::setPhoto(std::string newPhoto) {
	photo = newPhoto;
}

bool Dog::isValid() {
	return this->breed != "" && this->breed != "\n";
}


Dog initDogForTests() {
	
	Dog test = Dog("t1", "t2", 1, 1, "t3");
	return test;
}

void testGeters(){

	Dog test = initDogForTests();
	
	assert(test.getBreed() == "t1");
	assert(test.getName() == "t2");
	assert(test.getAge() == 1);
	assert(test.getPhoto() == "t3");
	assert(test.getWeight() == 1);
}

void testSeters(){

	Dog test = initDogForTests();
	
	assert(test.getBreed() == "t1");
	assert(test.getName() == "t2");
	assert(test.getAge() == 1);
	assert(test.getPhoto() == "t3");

	test.setBreed("T1");
	test.setName("T2");
	test.setAge(2);
	test.setPhoto("T3");

	assert(test.getBreed() == "T1");
	assert(test.getName() == "T2");
	assert(test.getAge() == 2);
	assert(test.getPhoto() == "T3");

}

void testEq() {

	Dog t1 = initDogForTests();
	Dog t2{ "t1", "t2", 3, 1, "4" };
	assert(t1 == t2);
}

void testLt() {
	Dog t1 = initDogForTests();
	assert(t1 < 10);
}

void testIsValid() {

	Dog d = initDogForTests();
	assert(d.isValid());
}

void testToString() {
	Dog d = initDogForTests();
	std::string test = "t1|t2|t3|1|1\n";
	assert(d.toStr() == test);
}

void testDomain() {

	testSeters();
	testGeters();
	testEq();
	testLt();
	testIsValid();
	testToString();
}



