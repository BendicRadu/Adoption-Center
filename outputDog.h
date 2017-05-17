#pragma once
#include "Domain.h"
#include "qstring.h"

class UiDog : public Dog {

public:

	UiDog(std::string breed, std::string name, int age, int weight, std::string photo);

	std::string toStr() const override {
		return "\nBreed: " + this->breed + "\nName: " + this->name + "\nAge: " + std::to_string(this->age) + "\nWeight: " + std::to_string(this->weight) + "\nPhoto: " + this->photo + "\n";
	}

	QString toQstr() {
		return QString::fromStdString(this->toStr());
	}

};

class  HtmlDog : public Dog {

public:

	HtmlDog(std::string breed, std::string name, int age, int weight, std::string photo);

	std::string toStr() const override {
		return "\n<tr><td>" + this->breed + "</td><td>" + this->name + "</td><td>" + std::to_string(this->age) + "</td><td>" + std::to_string(this->weight) + "</td><td><a href=\"" + this->photo + "\">Link</a></td></tr>";
	}

};


class  CsvDog : public Dog {

public:

	CsvDog(std::string breed, std::string name, int age, int weight, std::string photo);

	std::string toStr() const override {
		return this->breed + "," + this->name + "," + std::to_string(this->age) + "," + std::to_string(this->weight) + "," + this->photo + "\n";
	}

};
