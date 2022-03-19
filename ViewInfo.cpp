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