#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <direct.h>
#include "Functions.h"
#include "..\StormLib\StormLib.h"

class Archive {
	private:
		std::string _Path;
		std::string _Folder;
		HANDLE _hMpq;
		int _FCount;
		bool _Created;

		void ReadFilesFromFolder(const std::string Folder, const bool Subfolder);

	public:	
		Archive(const char* Path, const char* Folder, bool ModeExtract);
		~Archive();
		void ExtractAllFiles();
		void AddAllFiles();
};