#pragma once
#include <exception>
#include <string>

class RepoException : public std::exception {

private:
	std::string message;

public:
	RepoException(std::string message) { this->message = message; }
	const char* what() const noexcept override {
		return this->message.c_str();
	}

};


class ValidateException : public std::exception {

private:
	std::string message;

public:
	ValidateException(std::string message) { this->message = message; }
	const char* what() const noexcept override {
		return this->message.c_str();
	}

};