#include "..\Headers\Functions.h"

using namespace std;

vector<string> Split(const string input, const char splitter) {
	vector<string> output;
	int lastIndex = 0;
	int length = input.length();
	for (int i = 0; i < length; i++) {
		if (input[i] == splitter) {
			output.push_back(input.substr(0, i - lastIndex));
		}
		if (i == length - 1)
			output.push_back(input.substr(0, length));
	}
	return output;
}

const int GetLastIndexOf(const string input, const char find) {
	for (int i = input.length(); i >= 0; i--)
		if (input[i] == find)
			return i;
	return -1;
}

void PrintMainScreen() {
	cout << "###############################################################################" << endl;
	cout << "#                                                                             #" << endl;
	cout << "#    SLEx - StormLib Extractor (and packer)                                   #" << endl;
	cout << "#        by Maksim Karelov aka Ty3uK                                          #" << endl;
	cout << "#            (c)2013                                                          #" << endl;
	cout << "#-----------------------------------------------------------------------------#" << endl;
	cout << "#     Usage:                                                                  #" << endl;
	cout << "#            SLEx [map] [-p|-u] [folder]                                      #" << endl;
	cout << "#     Where:                                                                  #" << endl;
	cout << "#           [map]: full path to your map (with extension)                     #" << endl;
	cout << "#           -p: pack your files from [folder]                                 #" << endl;
	cout << "#           -u: pack your files to [folder]                                   #" << endl;
	cout << "#           [folder]: folder to pack\\unpack files to\\from map                 #" << endl;
	cout << "#     Example:                                                                #" << endl;
	cout << "#           SLEx MyCoolMap.w3x -p MyCoolFiles                                 #" << endl;
	cout << "#                                                                             #" << endl;
	cout << "###############################################################################" << endl << endl;
}