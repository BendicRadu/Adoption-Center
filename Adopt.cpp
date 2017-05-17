#include "Adopt.h"
#include <assert.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <windows.h>
#include "outputDog.h"
#include "qfile.h"
#include "qstring.h"
#include "qdatastream.h"

Dog AdoptList::getCurentDog() {
	
	Dog *d = this->dogs.data();
	if (d != NULL)
		return d[this->curent];
}

Dog* toHtmlDog(Dog d){ return new HtmlDog { d.getBreed(), d.getName(), d.getAge(), d.getWeight(), d.getPhoto() }; }
std::string toHtmlStr(Dog* d) { return d->toStr(); }

Dog* toCsvDog(Dog d) {return new CsvDog { d.getBreed(), d.getName(), d.getAge(), d.getWeight(), d.getPhoto() }; }
std::string toCsvStr(Dog* d) { return d->toStr(); }

void AdoptList::saveHtml() {

	std::string head = "<!DOCTYPE html>\n<style>.center {\npadding: 70px 0;\nborder: 0px solid green;\n}</style>\n<html>\n<head>\n<title>Adoption List</title>\n</head>\n<body >\n<div class=\"center\">\n<table align=\"center\" border=\"1\">\n<tr colspan=\"5\"><td colspan=\"5\" align=\"center\"  bgcolor=\"#AEE4EE\"><font size=\"8\">Adoption List</font></td></tr><tr>\n<td align=\"center\"><font size=\"6\">Breed</font></td>\n<td align=\"center\"><font size=\"6\">Name</font></td>\n<td align=\"center\"><font size=\"6\">Age</font></td>\n<td align=\"center\"><font size=\"6\">Weight</font></td>\n<td align=\"center\"><font size=\"6\">Photo</font></td>\n</tr>";
	std::string bottom = "\n</table>\n</div>\n</body>\n</html>";

	std::vector<Dog> v = this->getAdoptList();

	std::vector<Dog*> uiV;
	uiV.resize(v.size());
	std::transform(v.begin(), v.end(), uiV.begin(), toHtmlDog);

	std::vector<std::string> disp;
	disp.resize(v.size());
	std::transform(uiV.begin(), uiV.end(), disp.begin(), toHtmlStr);
	
	disp.insert(disp.begin(), head);
	disp.push_back(bottom);
	
	std::ofstream output_file(this->fileName);
    std::ostream_iterator<std::string> output_iterator(output_file);
    std::copy(disp.begin(), disp.end(), output_iterator);
	output_file.close();
}

void AdoptList::saveCsv() {
		
	std::vector<Dog> v = this->getAdoptList();
	std::vector<Dog*> csv;
	csv.resize(v.size());
	std::transform(v.begin(), v.end(), csv.begin(), toCsvDog);

	std::vector<std::string> disp;
	disp.resize(v.size());
	std::transform(csv.begin(), csv.end(), disp.begin(), toHtmlStr);

	std::ofstream output_file(this->fileName);
    std::ostream_iterator<std::string> output_iterator(output_file);
    std::copy(disp.begin(), disp.end(), output_iterator);
	output_file.close();
}

void AdoptList::save() {
	
	if (this->isHtml == true)
		this->saveHtml();
	else
		this->saveCsv();
}

void AdoptList::openAdoptList() {

	if (this->isHtml == true)
		ShellExecuteA(NULL, NULL, "chrome.exe", "list.html", NULL, SW_SHOWNORMAL);
	else
		ShellExecuteA(NULL, NULL, "notepad.exe", "list.csv", NULL, SW_SHOWNORMAL);
}

void AdoptList::next() {

	if (this->getVectorSize() == 0) {
		return;
	}

	if (this->curent == this->getVectorSize() - 1)
		this->curent = -1;
	this->curent++;

}

void AdoptList::openPhoto() { getCurentDog().play(); }

std::vector<Dog> AdoptList::filterDogs(std::string breed, int age) {
	
	std::vector<Dog> filter (this->dogs.size());
	
	auto it = std::copy_if(this->dogs.begin(), this->dogs.end(), filter.begin(), [breed, age](Dog d) { return d.getAge() <= age && d.getBreed() == breed; });
	filter.resize(std::distance(filter.begin(), it));

	return filter;
}

AdoptList initAdoptListTest() {

	AdoptList test{};
	return test;
}

void testAdoptAdd() {
	AdoptList a = initAdoptListTest();
	Dog b{ "T1", "T1", 3, 1, "T1" };
	Dog c{ "T2", "T2", 3, 1, "T2" };
	a.addDogToVector(b);
	a.addDogToVector(c);

	assert(a.getVectorSize() == 2);

	a.adoptDog();
	assert(a.getAdoptSize() == 1);
	assert(a.adoptGetDogOnPos(0) == b);
	
	a.next();

	a.adoptDog();
	assert(a.getAdoptSize() == 2);
	assert(a.adoptGetDogOnPos(1) == c);
}

void testGetCurent() {
	AdoptList a = initAdoptListTest();
	Dog b{ "T1", "T1", 3, 1, "T1" };
	Dog c{ "T2", "T2", 3, 1, "T2" };
	a.addDogToVector(b);
	a.addDogToVector(c);

	assert(a.getVectorSize() == 2);

	assert(a.getCurentDog() == b);

	a.next();
	assert(a.getCurentDog() == c);

	a.next();
	assert(a.getCurentDog() == b);

}

void testFilter() {
	AdoptList a = initAdoptListTest();
	Dog b{ "T1", "T1", 3, 4, "T1" };
	Dog c{ "T2", "T2", 3, 4, "T2" };

	a.addDogToVector(b);
	a.addDogToVector(c);

	std::vector<Dog> test{ a.filterDogs("T1", 4) };

	assert(test[0] == b);
	assert(test.size() == 1);

}

void testRemove() {

	AdoptList a = initAdoptListTest();
	Dog b{ "1", "2", 3, 4, "5" };
	a.addDogToVector(b);
	a.removeAdoptedDog();
	assert(a.getVectorSize() == 0);
}

void testSetVector() {

	AdoptList a = initAdoptListTest();
	std::vector<Dog> test;

	Dog b{ "T1", "T1", 3, 4, "T1" };
	Dog c{ "T2", "T2", 3, 4, "T2" };

	test.push_back(b);
	test.push_back(c);

	a.setVector(test);
}

void testAdoptList() {

	AdoptList a = initAdoptListTest();
	Dog b{ "T1", "T1", 3, 4, "T1" };
	Dog c{ "T2", "T2", 3, 4, "T2" };

	a.addDogToVector(b);
	a.addDogToVector(c);

	std::vector<Dog> d = a.getAdoptList();

	a.resetCurent();
	assert(a.getCurentPos() == 0);
}

void testAdopt() {
	testAdoptAdd();
	testGetCurent();
	testFilter();
	testRemove();
	testSetVector();
	testAdoptList();
}













