#include "Test.hpp"

Test::Test(const string& rep_str, size_t pos) {
	string elem;
	size_t pos_begin = rep_str.find("id", pos);
	pos_begin += 4;
	size_t pos_end = rep_str.find(",", pos_begin);
	elem = rep_str.substr(pos_begin, pos_end - pos_begin);
	this->id = atoi(elem.c_str());
	pos_begin = rep_str.find("title", pos_end);
	pos_begin += 9;
	pos_end = rep_str.find("\",", pos_begin);
	this->title = rep_str.substr(pos_begin, pos_end - pos_begin);
}

Test::~Test() {}

Test::Test(const Test &orig) {
	*this = orig;
}

vector<Test> &Test::getValues() {
	return this->values;
}

void Test::setValueById(map<unsigned, string> &value_map) {
	this->value = value_map[this->id];
	int size = this->values.size();
	for (int i = 0; i < size; i++)
		this->values[i].setValueById(value_map);
}

Test &Test::operator=(const Test &orig) {
	if (this == &orig)
		return *this;
	this->id = orig.id;
	this->title = orig.title;
	this->value = orig.value;
	this->values = orig.values;
	return (*this);
}

const unsigned Test::getId() {
	return this->id;
}

const string &Test::getTitle() {
	return this->title;
}

const string &Test::getValue() {
	return this->value;
}

std::ostream& operator<<(std::ostream& out, Test& orig) {
	out << "{\"id\": " << orig.getId() << ",";
	out << "\"title\": \"" << orig.getTitle() << "\",";
	out << "\"value\": \"" << orig.getValue() << "\"";
	int size = orig.getValues().size();
	if (size > 0) {
		out << ",\"values\":\n[";
		for (int i = 0; i < size - 1; i++) {
			out << orig.getValues()[i];
			out << ",";
		}
		out << orig.getValues()[size - 1]; 
		out << "]";
	}
	out << "}";
	return out;
}