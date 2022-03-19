#include"ViewInfo.h"
ViewInfo::~ViewInfo() {
	deViewInfo();
}

void ViewInfo::deViewInfo() {
	for (int i = 0; i < headerCount; ++i) {
		delete[] header[i];
		delete[] info[i];
	}
	delete[]header;
	delete[]info;
}

void ViewInfo::viewInfo(char filename[], int stt) {
	ifstream in;
	in.open(filename);
	if (!in.is_open()) {
		cout << "Sorry, our service encountered an error, please retry!" << endl;
		return;
	}
	in >> headerCount;
	in.ignore(50, '\n');

	header = new char*[headerCount];
	info = new char*[headerCount];
	for (int i = 0; i < headerCount; ++i) {
		header[i] = new char[50];
		info[i] = new char[100];
	}

	for (int i = 0; i < headerCount; ++i) {

		if (i != headerCount - 1) {
			in.get(header[i], 50, ',');
			in.ignore(2, ',');
		}
		else {
			in.get(header[i], 50, '\n');
			in.ignore(2, '\n');
		}
	}

	for (int i = 0; i < stt; ++i) {
		in.ignore(1000, '\n');
	}

	for (int i = 0; i < headerCount; ++i) {

		if (i != headerCount - 1) {
			in.get(info[i], 50, ',');
			in.ignore(2, ',');
		}
		else {
			in.get(info[i], 50, '\n');
			in.ignore(2, '\n');
		}
		if (info[i][0] == '#')continue;
		else if (header[i][0] != '*')cout << header[i] << ": " << info[i] << endl;
		else cout << header[i] << endl;
	}
}
