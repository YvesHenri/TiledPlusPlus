#ifndef TPP_FILE_PATH_H
#define TPP_FILE_PATH_H

#include <string>

#include "Macros\OS.h"
#include "Macros\Exporter.h"

namespace tpp
{
	class TILEDPP_API Path final
	{
	public:
		static bool FileExists(std::string path);
		static bool PathExists(std::string path);
		static bool IsPath(std::string path);
		static bool IsFile(std::string path);

		Path(std::string path);
		~Path() = default;

		std::string getFileName(bool validate = true);
		std::string getFileFullName(bool validate = true);
		std::string getFileExtension(bool validate = true);

		Path& operator=(const char* path);
		Path& operator=(std::string& path);

	public:
		static std::string Separator;

	private:
		std::string m_filePath;
		std::string m_fileName;
		std::string m_fileFullName;
		std::string m_fileFullPath;
		std::string m_fileExtension;
	};
}

#endif