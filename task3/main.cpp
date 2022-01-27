#include "Test.hpp"

size_t parse_report_str(vector<Test> &tests, const string &rep_str, size_t pos) {
	if (pos != string::npos)
		pos++;
	else
		return pos;
	size_t pos_open = rep_str.find("{", pos);
	size_t pos_close = rep_str.find("}", pos);
	Test test(rep_str, pos);
	if (pos_open != string::npos && pos_open < pos_close)
		pos_open = parse_report_str(test.getValues(), rep_str, pos_open);
	tests.push_back(test);
	if (pos_open != string::npos)
		pos_open++;
	pos = pos_open;
	return pos;
}

void file_to_rep_str(vector<Test> &tests, ifstream &report) {
	string line;
	string rep_str;
	size_t pos;
	while (getline(report, line))
		rep_str.append(line);
	pos = rep_str.find("[");
	pos = rep_str.find("{", pos);
	while (pos != string::npos)
		pos = parse_report_str(tests, rep_str, pos);
}

void file_to_values_str(map<unsigned, string> &values_map, ifstream &values) {
	string line;
	string values_str;
	unsigned id;
	while (getline(values, line))
		values_str.append(line);
		string elem;
	size_t pos_begin = values_str.find("id");
	while (pos_begin != string::npos) {
		pos_begin += 4;
		size_t pos_end = values_str.find(",", pos_begin);
		elem = values_str.substr(pos_begin, pos_end - pos_begin);
		id = atoi(elem.c_str());
		pos_begin = values_str.find("value", pos_end);
		pos_begin += 9;
		pos_end = values_str.find("\"", pos_begin);
		values_map[id] = values_str.substr(pos_begin, pos_end - pos_begin);
		pos_begin = values_str.find("id", pos_end);
	}
}

int main(int argc, char *argv[]) {
	vector<Test> tests;
	map<unsigned, string> values_map;
	if (argc != 3)
		return (0);
	ifstream report(argv[1]), values(argv[2]);
	if (!report.is_open() || !values.is_open())
		return (0);
	file_to_rep_str(tests, report);
	file_to_values_str(values_map, values);
	report.close();
	values.close();
	int tests_size = tests.size();
	for (int i = 0; i < tests_size; i++)
		tests[i].setValueById(values_map);
			/*
	for (auto test : tests)
		test.setValueById(values_map);
		*/
	ofstream out("report.json");
	out << "{\"tests\": \n[";
	int size = tests.size();
	for (int i = 0; i < size - 1; i++) {
		out << tests[i];
		out << ",";
	}
	out << tests[size - 1];
	out << "]}";
	out.close();
	return (0);
}