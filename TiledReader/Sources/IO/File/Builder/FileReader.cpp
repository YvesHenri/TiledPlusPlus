#include "IO\File\Builder\FileReader.h"

namespace tpp
{
	tpp::File FileReader::read(const std::string& path)
	{
		tpp::FileMetadata metadata = m_parser.parseMetadata(path);

		for (const auto& layer : metadata.layers)
		{
			if (layer->material == tpp::Material::Tile)
				//decompress(*static_cast<tpp::TileLayer*>(layer));
				continue;
		}

		return tpp::File(path, metadata);
	}

	void FileReader::decompress(tpp::TileLayer& layer)
	{
		// Create a tile outside the loop to speed up things. It will be reused as many times as needed
		tpp::Tile tile;
		std::string decoded = tpp::Decoder::decode(layer.data.value, layer.data.compression, layer.data.encoding);

		for (unsigned int index = 0; index < layer.area; index++)
		{
			// Reserves 4 bytes for each tile, since encoded tile gids are composed by 4 bytes
			unsigned int encodingIndex = index * 4;

			// Decodes the gid by shifting left each byte of a gid (see 'Tiled' main page: mapeditor.org)
			tile.gid = static_cast<unsigned char>(decoded[encodingIndex])
				| static_cast<unsigned char>(decoded[encodingIndex + 1]) << 8
				| static_cast<unsigned char>(decoded[encodingIndex + 2]) << 16
				| static_cast<unsigned char>(decoded[encodingIndex + 3]) << 24;

			// Update the linear 1D position
			tile.index = index;

			// Get the owner
			tile.owner = &layer;

			// Reuse the function. Let it set positions, owner, etc
			// dispatch(tile);
		}
	}
}