#pragma once
#include <string>
#include "Domain.h"
#include "Exceptions.h"

class Validate {

private:
	static bool containsNumber(std::string str) {
		
		for (char i = '0'; i <= '9'; i++) {
			if (str.find(i) != std::string::npos)
				return true;
		}
		return false;
	}

	static bool containsLetter(std::string str) {
		
		for (char i = 0; i < str.size(); i++) {
			if (str[i] < '0' || str[i] > '9')
				return true;
		}
		return false;
	}

public:
	
	static void validate(Dog& d) {
		
		std::string error;

		if (containsNumber(d.getBreed())) {
			error += "Error: Dog breed cannot contain numbers\n";
		}

		if (containsNumber(d.getName())) {
			error += "Error: Dog name cannot contain numbers\n";
		}

		if (containsLetter(std::to_string(d.getAge()))) {
			error += "Error: Dog age cannot contain letters\n";
		}

		if (d.getAge() <= 0) {
			error += "Error: Dogs can't have negative ages\n";
		}

		if (d.getAge() >= 21) {
			error += "Error: Dogs can't be that old\n";
		}

		if (containsLetter(std::to_string(d.getWeight()))) {
			error += "Error: Dog weight cannot contain letters\n";
		}

		if (error.size() > 0)
			throw ValidateException(error);

	}

	static void validateInt(std::string num) {
		
		std::string error;

		if (containsLetter(num)) {
			error += "Error: Numbers don't contain letters\n";
		}

		if (error.size() > 0)
			throw ValidateException(error);
	}

};