#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>

using namespace std;

class Test {
	private:
		unsigned id;
		string title;
		string value;
		vector<Test> values;
		Test();
	public:
		Test(const string& rep_str, size_t pos);
		~Test();
		const unsigned getId();
		const string &getTitle();
		const string &getValue();
		Test(const Test &orig);
		Test &operator=(const Test &orig);
		void setValueById(map<unsigned, string> &value_map);
		vector<Test> &getValues() ;
};

std::ostream& operator<<(std::ostream& out, Test& orig);
