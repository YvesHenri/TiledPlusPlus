#ifndef TPP_FILE_PATH_H
#define TPP_FILE_PATH_H

#include <string>

#include "Macros\OS.h"
#include "Macros\API.h"

namespace tpp
{
	class TILEDPP_API Path final
	{
	public:
		static bool IsPath(const std::string& path);
		static bool IsFile(const std::string& path);

		static bool FileExists(const std::string& path);
		static bool PathExists(const std::string& path);

		static std::string ToFilePath(const std::string& path, bool validate = true);
		static std::string ToFileName(const std::string& path, bool validate = true);
		static std::string ToFileFullName(const std::string& path, bool validate = true);
		static std::string ToFileExtension(const std::string& path, bool validate = true);

		Path(const std::string& path);

		const std::string& getFileName() const;
		const std::string& getFilePath() const;
		const std::string& getFileFullPath() const;
		const std::string& getFileFullName() const;
		const std::string& getFileExtension() const;

		Path& operator=(const char* path);
		Path& operator=(const std::string& path);

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