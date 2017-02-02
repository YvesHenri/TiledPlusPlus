#include "File\Path.h"

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
		return true;
	}

	bool Path::IsFile(std::string path)
	{
		return true;
	}

	Path::Path(std::string path)
		: m_path(path)
	{}

	std::string Path::getFileName(bool validate)
	{
		return "";
	}

	std::string Path::getFileFullName(bool validate)
	{
		return "";
	}

	std::string Path::getFileExtension(bool validate)
	{
		return "";
	}
}