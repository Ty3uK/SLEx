#include "..\Headers\Archive.h"

using namespace std;

Archive::Archive(const char* Path, const char* Folder, bool ModeExtract) {
	this->_hMpq = NULL;
	this->_Path = Path;
	this->_Folder = Folder;
	if (Folder[strlen(Folder) - 1] != '\\')
		this->_Folder += '\\';
	this->_Created = GetFileAttributes(Path) == -1;
	if (!this->_Created)
		SFileOpenArchive(Path, NULL, SFILE_OPEN_FROM_MPQ, &this->_hMpq);
	else if (!ModeExtract)
		SFileCreateArchive(Path, NULL, HASH_TABLE_SIZE_MAX, &this->_hMpq);
	else
		exit(1);
	this->_FCount = 0;
}

Archive::~Archive() {
	if (this->_Created)
		SFileSetMaxFileCount(this->_hMpq, HASH_TABLE_SIZE_MIN + this->_FCount);

		SFileCompactArchive(this->_hMpq, NULL, NULL);
		SFileCloseArchive(this->_hMpq);
}

void Archive::ExtractAllFiles() {
	string path;
	vector<string> tree;
	int splitter;
	SFILE_FIND_DATA CurrentFile, FindFile;
	HANDLE hFindFile = SFileFindFirstFile(this->_hMpq, "*", &FindFile, NULL);

	_mkdir(this->_Folder.c_str());

	while (SFileFindNextFile(hFindFile, &CurrentFile)) {
		path = CurrentFile.cFileName;
		splitter = GetLastIndexOf(path, '\\');
		if (splitter > 0) {
			tree = Split(this->_Folder + path.substr(0, splitter), '\\');
			for (int i = 0; i < tree.size(); i++)
				_mkdir(tree[i].c_str());
		}
		cout << "Extracting: " << CurrentFile.cFileName << endl;
		SFileExtractFile(this->_hMpq, CurrentFile.cFileName, (this->_Folder + path).c_str(), NULL);
	}

	SFileFindClose(hFindFile);
}

void Archive::AddAllFiles() {
	Archive::ReadFilesFromFolder(this->_Folder, false);
}

void Archive::ReadFilesFromFolder(string Folder, const bool Subfolder) {
	WIN32_FIND_DATA data;
	HANDLE hFind = FindFirstFile((Folder + "*").c_str(), &data);
	string FilePath;

	while (FindNextFile(hFind, &data)) {
		if (!(data.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)) {
			if (!Subfolder)
				FilePath = data.cFileName;
			else
				FilePath = Folder.substr(this->_Folder.length()) + data.cFileName;

			cout << "Packing: " << FilePath << endl;
			this->_FCount++;
			SFileAddFileEx(this->_hMpq, (this->_Folder + FilePath).c_str(), FilePath.c_str(), MPQ_FILE_COMPRESS | MPQ_FILE_REPLACEEXISTING, MPQ_COMPRESSION_ZLIB, MPQ_COMPRESSION_ZLIB);
		} else if (strcmp(data.cFileName, "..") != NULL) {
			this->_FCount++;
			ReadFilesFromFolder(Folder + data.cFileName + '\\', true);
		}
	}

	FindClose(hFind);
}