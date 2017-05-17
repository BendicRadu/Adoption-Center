#include "outputDog.h"

UiDog::UiDog(std::string breed, std::string name, int age, int weight, std::string photo) : Dog{ breed, name, age, weight, photo } {};

HtmlDog::HtmlDog(std::string breed, std::string name, int age, int weight, std::string photo) : Dog{ breed, name, age, weight, photo } {};

CsvDog::CsvDog(std::string breed, std::string name, int age, int weight, std::string photo) : Dog{ breed, name, age, weight, photo } {};