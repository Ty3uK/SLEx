#include <iostream>
#include "..\Headers\Archive.h"
#include "..\Headers\Functions.h"
#include "..\StormLib\StormLib.h"

using namespace std;

int main(int argc, char* argv[]) {
	PrintMainScreen();
	if (argc == 4) {
		bool ModeExtract = strcmp(argv[2], "-p") == 0;
		Archive Map(argv[1], argv[3], !ModeExtract);
		if (ModeExtract)
			Map.AddAllFiles();
		else
			Map.ExtractAllFiles();
	}

	cout << endl;
	system("pause");
	return 0;
}