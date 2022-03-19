#include"Utils.h"

fstream & GotoLine(fstream & file, int num)
{
	file.seekg(ios::beg);
	for (int i = 0; i <= num - 1; ++i) {
		file.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return file;
}