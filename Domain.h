#pragma once
#include <iostream>
#include <string>
#include "qstring.h"

class Dog {

protected:
	std::string breed;
	std::string name;
	int age;
	int weight;
	std::string photo;

public:

	//Default constructor
	Dog();

	//Constructor with parameters
	Dog(const std::string& breed, const std::string& name, const int& age, const int& weight, const std::string& photo);
	virtual ~Dog() {};

	//Getters for the Dog class fields
	std::string getBreed() const { return this->breed; }
	std::string getName() const { return this->name; }
	int getAge() const { return this->age; }
	int getWeight() const { return this->weight; }
	std::string getPhoto() const { return this->photo; }


	//Setters for the Dog class fileds
	void setBreed(std::string newBreed);
	void setName(std::string newName);
	void setAge(int newAge);
	void setPhoto(std::string newPhoto);
	

	Dog& operator = (const Dog&d) {
		this->breed = d.getBreed();
		this->name = d.getName();
		this->age = d.getAge();
		this->weight = d.getWeight();
		this->photo = d.getPhoto();
		return *this;
	}

	virtual QString toQstr() const{
		return QString::fromStdString(this->toStr());
	}

	bool operator == (const Dog& d) {
		return (this->breed == d.getBreed() && this->name == d.getName());
	}

	bool operator < (const int weight) {
		return  (this->weight < weight);
	}

	friend std::istream& operator >> (std::istream& input, Dog& d) {
		std::getline(input, d.breed, '|');
		std::getline(input, d.name, '|');
		std::getline(input, d.photo, '|' );
		input >> d.age;
		input.ignore(1, '|');
		input >> d.weight;
		input.get();
		return input;
	}

	
	virtual std::string toStr() const {
		return this->breed + "|" + this->name + "|" + this->photo + "|" + std::to_string(this->age) + "|" + std::to_string(this->weight) + "\n";
	}


	friend std::ostream& operator << (std::ostream& output, const Dog& d){
		output << d.toStr();
		return output;
	}

	bool isValid();

	void play();
};

void testDomain();