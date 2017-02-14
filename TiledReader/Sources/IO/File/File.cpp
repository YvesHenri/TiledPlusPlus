#include "IO\File\File.h"

namespace tpp
{
	File::File(const tpp::Path& path, tpp::FileMetadata& metadata)
		: m_path(path)
		, m_metadata(std::move(metadata))
	{}

	const tpp::Path& File::getPath() const
	{
		return m_path;
	}

	const tpp::Header& File::getHeader() const
	{
		return m_metadata.header;
	}

	const tpp::TileSets& File::getTileSets() const
	{
		return m_metadata.sets;
	}

	const tpp::Layers& File::getLayers() const
	{
		return m_metadata.layers;
	}
}