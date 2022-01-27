#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
	int n,m, pos = 1;
	if (argc == 1)
		cin >> n >> m;
	else if (argc == 2) {
		ifstream file(argv[1]);
		if (!file.is_open())
		return (0);
		file >> n >> m;
		file.close();
	}
	else if (argc == 3) {
		n = atoi(argv[1]);
		m = atoi(argv[2]);
	}
	else
		return (0);
	do {
		cout << pos;
		pos = (pos + m - 1) % n;
		if (pos == 0)
			pos = n;
	}
	while (pos != 1);
	cout << endl;
	return (0);
}