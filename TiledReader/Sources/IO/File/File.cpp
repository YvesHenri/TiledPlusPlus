#include "IO\File\File.h"

namespace tpp
{
	File::File(std::string path, tpp::FileMetadata metadata)
		: m_metadata(metadata)
	{
		// Fetch extra file info if path specifies a valid string
		if (!path.empty())
		{
			unsigned int extensionOccurrenceIndex = path.find_last_of(".");
			unsigned int nameOccurrenceIndex = path.find_last_of(tpp::Path::Separator);

			if (extensionOccurrenceIndex != std::string::npos) {
				m_extension = path.substr(extensionOccurrenceIndex + 1U);
			}

			if (nameOccurrenceIndex != std::string::npos) {
				m_name = path.substr(nameOccurrenceIndex + 1U);
			}

			if (nameOccurrenceIndex != std::string::npos) {
				m_path = path.substr(0, nameOccurrenceIndex + 1U);
			}
		}
	}

	const std::string& File::getName()
	{
		return m_name;
	}

	const std::string& File::getPath()
	{
		return m_path;
	}

	const std::string& File::getFullPath()
	{
		return m_fullPath;
	}

	const tpp::Header& File::getHeader()
	{
		return m_metadata.header;
	}

	const tpp::TileSets& File::getTileSets()
	{
		return m_metadata.tileSets;
	}

	const tpp::TileLayers& File::getTileLayers()
	{
		return m_metadata.tileLayers;
	}

	const tpp::ImageLayers& File::getImageLayers()
	{
		return m_metadata.imageLayers;
	}

	const tpp::ObjectLayers& File::getObjectLayers()
	{
		return m_metadata.objectLayers;
	}

	bool File::isParsable() const
	{
		return isValidExtension() && tpp::Path::FileExists(m_fullPath);
	}

	bool File::isValidExtension() const
	{
		return m_extension == "tmx";
	}
}