#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

float distance_pow2(pair<float, float> point1, pair<float, float> point2) {
	return (pow(point2.first - point1.first, 2) + pow(point2.second - point1.second, 2));
}

void parse_file1(pair<float, float> &circle, float &R_pow2, ifstream &file1) {
	file1 >> circle.first >> circle.second >> R_pow2;
	R_pow2 = pow(R_pow2, 2);
}

void parse_file2(vector<pair<float, float>> &points, ifstream &file2) {
	pair<float, float> point;
	while (file2 >> point.first >> point.second) {
		points.push_back(point);
	}
}

int main(int argc, char *argv[]) {
	float R_pow2;
	pair<float, float> circle;
	vector<pair<float, float>> points;
	if (argc != 3)
		return (0);
	ifstream file1(argv[1]), file2(argv[2]);
	if (!file1.is_open() || !file2.is_open())
		return (0);
	parse_file1(circle, R_pow2, file1);
	parse_file2(points, file2);
	file1.close();
	file2.close();
	for (auto point : points) {
		float distance = distance_pow2(circle, point);
		if (distance > R_pow2)
			cout << 2;
		else if (distance < R_pow2)
			cout << 1;
		else
			cout << 0;
		cout << endl;
	}
	return (0);
}