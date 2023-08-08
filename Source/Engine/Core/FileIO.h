#pragma once
#include <filesystem> //apart of new C++
#include <string>

//dont use using namespace std in headers, can get confusing
//forces anyone who uses the header to ALSO use the namespace std


namespace minimum
{
	std::string getFilePath();
	bool setFilePath(const std::filesystem::path& path);
	std::string getFileName(const std::filesystem::path& path);

	bool fileExists(const std::filesystem::path& path);
	bool getFileSize(const std::filesystem::path& path, size_t& size);
	bool readFile(const std::filesystem::path& path, std::string& buffer);

}