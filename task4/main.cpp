#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

void parse_file(vector<int> &arr, ifstream &file) {
	int num;
	while (file >> num) {
		arr.push_back(num);
	}
}

long find_mid(const vector<int> &arr) {
	long delta,mid,sum = 0;
	unsigned size = arr.size();
	for (auto num : arr)
		sum += num;
	mid = sum / size;
	delta = sum % size;
	if (delta > size - delta)
		mid++;
	return mid;
}

int main(int argc, char *argv[]) {
	long mid, sum = 0;
	vector<int> arr;
	if (argc != 2)
		return (0);
	ifstream file(argv[1]);
	if (!file.is_open())
		return (0);
	parse_file(arr, file);
	file.close();
	mid = find_mid(arr);
	for (auto num : arr)
		sum += abs(mid - num);
	cout << sum << endl;
	return (0);
}