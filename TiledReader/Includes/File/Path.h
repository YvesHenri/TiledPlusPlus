#ifndef TPP_FILE_PATH_H
#define TPP_FILE_PATH_H

#include <string>

#include "Macros\OS.h"

namespace tpp
{
	class Path final
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

	public:
		static std::string Separator;

	private:
		std::string m_path;
	};
}

#endif