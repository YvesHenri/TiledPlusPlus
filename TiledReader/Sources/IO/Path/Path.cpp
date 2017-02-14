#include "IO\Path\Path.h"

namespace tpp
{
	#if defined (TILEDPP_OS_WINDOWS)
		std::string Path::Separator = "//";
	#else
		std::string Path::Separator = "\";
	#endif

	bool Path::FileExists(const std::string& path)
	{
		return true;
	}

	bool Path::PathExists(const std::string& path)
	{
		return true;
	}

	bool Path::IsPath(const std::string& path)
	{
		return Path::PathExists(path) && true;
	}

	bool Path::IsFile(const std::string& path)
	{
		return Path::FileExists(path) && true;
	}

	std::string Path::ToFilePath(const std::string& path, bool validate)
	{
		std::string simplified("");

		if (validate && !Path::IsFile(path))
			throw std::runtime_error("Path does not specify a valid file path");

		auto separatorIndex = path.find_last_of(Path::Separator);

		if (separatorIndex != std::string::npos)
			simplified = path.substr(0U, separatorIndex + 1U);
		
		return simplified;
	}

	std::string Path::ToFileName(const std::string& path, bool validate)
	{
		std::string name("");

		if (validate && !Path::IsFile(path))
			throw std::runtime_error("Path does not specify a valid file path");

		auto extensionIndex = path.find_last_of(".");
		auto separatorIndex = path.find_last_of(Path::Separator);

		// If theres a dot (extension delimiter), return whatever comes after it
		if (separatorIndex != std::string::npos)
			name = path.substr(separatorIndex + 1U, extensionIndex - separatorIndex - 1U);

		return name;
	}

	std::string Path::ToFileFullName(const std::string& path, bool validate)
	{
		std::string fullName("");

		// If theres no validation, skip the path validation (extensionless files etc)
		if (validate && !Path::IsFile(path))
			throw std::runtime_error("Path does not specify a valid file path");

		auto separatorIndex = path.find_last_of(Path::Separator);

		// If theres a path sepparator, return whatever comes after it
		if (separatorIndex != std::string::npos)
			fullName = path.substr(separatorIndex + 1U);
		
		return fullName;
	}

	std::string Path::ToFileExtension(const std::string& path, bool validate)
	{
		std::string extension("");

		// If theres no validation, skip the path validation (extensionless files etc)
		if (validate && !Path::IsFile(path))
			throw std::runtime_error("Path does not specify a valid file path");

		auto extensionIndex = path.find_last_of(".");

		// If theres a dot (extension delimiter), return whatever comes after it
		if (extensionIndex != std::string::npos)
			extension = path.substr(extensionIndex + 1U);

		return extension;
	}

	Path::Path(const std::string& path)
	{
		m_filePath = Path::ToFilePath(path, false);
		m_fileName = Path::ToFileName(path, false);
		m_fileFullName = Path::ToFileFullName(path, false);
		m_fileFullPath = path;
		m_fileExtension = Path::ToFileExtension(path, false);
	}

	const std::string& Path::getFileName() const
	{
		return m_fileName;
	}

	const std::string& Path::getFilePath() const
	{
		return m_filePath;
	}

	const std::string& Path::getFileFullPath() const
	{
		return m_fileFullPath;
	}

	const std::string& Path::getFileFullName() const
	{
		return m_fileFullName;
	}

	const std::string& Path::getFileExtension() const
	{
		return m_fileExtension;
	}

	Path& Path::operator=(const char* path)
	{
		return operator=(std::string(path));
	}

	Path& Path::operator=(const std::string& path)
	{
		if (!path.empty())
		{
			m_filePath = Path::ToFilePath(path, false);
			m_fileName = Path::ToFileName(path, false);
			m_fileFullName = Path::ToFileFullName(path, false);
			m_fileFullPath = path;
			m_fileExtension = Path::ToFileExtension(path, false);
		}

		return *this;
	}
}