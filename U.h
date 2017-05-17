#pragma once
#include "Domain.h"


class UiDog : public Dog {

public:

	UiDog(std::string breed, std::string name, int age, int weight, std::string photo);
	~UiDog() {};

	std::string toStr() const override {
		return "\nBreed: " + this->getBreed() + "\n" + "Name: " + this->getName() + "\n" + "Age: " + std::to_string(this->getAge()) + "\n" + "Weight (Kg): " + std::to_string(this->getWeight()) + "\n" + "Link: " + this->getPhoto() + "\n";
	}

	QString toQstr() const override {
		return QString::fromStdString(this->toStr());
	}
};

class HtmlDog : public Dog {

public:

	HtmlDog(std::string breed, std::string name, int age, int weight, std::string photo);
	~HtmlDog() {};

	std::string toStr() const override {
		return "\n<tr>\n<td align=\"center\" width=\"400\" height = \"400\" ><font size=\"5\">" + this->getBreed() + "</font></td>\n<td align=\"center\" width=\"400\" height = \"400\" ><font size=\"5\">" + this->getName() + "</font></td>\n<td align=\"center\" width=\"400\" height = \"400\"><font size=\"5\">" + std::to_string(this->getAge()) + "</font></td>\n<td align=\"center\" width=\"400\" height = \"400\"><font size=\"5\">" + std::to_string(this->getWeight()) + "</font></td>\n<td align=\"center\" width=\"400\" height = \"400\"><img src=" + this->getPhoto() + " style=\"width:400px;height:400px;\"></td>\n</tr>";
	}
};

class CsvDog : public Dog {

public:
	CsvDog(std::string breed, std::string name, int age, int weight, std::string photo);
	~CsvDog() {};

	std::string toStr() const override {
		return this->getBreed() + "," + this->getName() + "," + std::to_string(this->getAge()) + "," + std::to_string(this->getWeight()) + "," + this->getPhoto() + "\n";
	}
};