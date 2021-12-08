#include <iostream>
#include <fstream>
using namespace std;

#define SIZE_FIELD 12

int main(int argc, char* argv[]) {
	string line;
	int nlines = 0;
	int bitfield[SIZE_FIELD];
	unsigned int rateGamma = 0;
	unsigned int rateEpsilon = 0;

	// error check
	if (argc != 2) {
		cerr << "usage: " << argv[0] << " <input-file>.\n";
		exit(1);
	}

	// set bitfield to zero
	for (int i = 0; i < SIZE_FIELD; i++) bitfield[i] = 0;

	// open file for reading
	ifstream fin(argv[1]);
	if (fin.is_open()) {

		// read file and count number of occurences of 1s in each line
		while (getline(fin, line)) {
			for (int i = 0; i < SIZE_FIELD; i++)
				if (line[i] - '0' == 1) bitfield[i]++;
			nlines++;
		}
		fin.close();
	} else {
		cerr << argv[0] << ": unable to read file.\n";
		exit(1);
	}

	// calculate bits in bitfield to form integer for rates
	for (int i = 0; i < SIZE_FIELD; i++) {
		// get most/least common bit
		int mcb = bitfield[i] > nlines-bitfield[i] ? 1 : 0;
		int lcb = ~mcb & 0x1;

		// bitshift each bit to form the integer
		rateGamma += mcb << (SIZE_FIELD-i-1);
		rateEpsilon += lcb << (SIZE_FIELD-i-1);
	}

	cout << "Read gamma rate " << rateGamma << " and epsilon rate " << rateEpsilon << " to yield product " << (rateGamma * rateEpsilon) << ".\n";
}
