#include "IO\Path\Path.h"

namespace tpp
{
	#if defined (TILEDPP_OS_WINDOWS)
		std::string Path::Separator = "//";
	#else
		std::string Path::Separator = "\";
	#endif

	bool Path::FileExists(std::string path)
	{
		return true;
	}

	bool Path::PathExists(std::string path)
	{
		return true;
	}

	bool Path::IsPath(std::string path)
	{
		return Path::PathExists(path) && true;
	}

	bool Path::IsFile(std::string path)
	{
		return Path::FileExists(path) && true;
	}

	Path::Path(std::string path)
	{}

	std::string Path::getFileName(bool validate)
	{
		if (validate && !Path::IsFile(m_fileFullPath))
			throw std::runtime_error("Path does not specify a valid file path");

		auto fileFullName = getFileFullName(validate);
		auto occurrenceIndex = fileFullName.find_last_of(".");

		// If theres a dot (extension delimiter), return whatever comes after it
		return occurrenceIndex != std::string::npos ? fileFullName.substr(0, occurrenceIndex + 1U) : "";
	}

	std::string Path::getFileFullName(bool validate)
	{
		// If theres no validation, skip the path validation (extensionless files etc)
		if (validate && !Path::IsFile(m_fileFullPath))
			throw std::runtime_error("Path does not specify a valid file path");

		unsigned int occurrenceIndex = m_fileFullPath.find_last_of(Path::Separator);

		// If theres a path sepparator, return whatever comes after it
		return occurrenceIndex != std::string::npos ? m_fileFullPath.substr(occurrenceIndex + 1U) : "";
	}

	std::string Path::getFileExtension(bool validate)
	{
		// If theres no validation, skip the path validation (extensionless files etc)
		if (validate && !Path::IsFile(m_fileFullPath))
			throw std::runtime_error("Path does not specify a valid file path");

		unsigned int occurrenceIndex = m_fileFullPath.find_last_of(".");

		// If theres a dot (extension delimiter), return whatever comes after it
		return occurrenceIndex != std::string::npos ? m_fileFullPath.substr(occurrenceIndex + 1U) : "";
	}

	Path& Path::operator=(const char* path)
	{
		return operator=(std::string(path));
	}

	Path& Path::operator=(std::string& path)
	{
		if (!path.empty())
		{
			m_fileFullPath = path;
		}

		return *this;
	}
}