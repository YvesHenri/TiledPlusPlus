#include "IO\File\Builder\FileReader.h"

namespace tpp
{
	FileReader::FileReader()
	{
		m_parser.onHeaderParsed.attach(evt::Delegate<void(tpp::Header*)>(&FileReader::onHeaderParsed, this));
	}

	tpp::File FileReader::read(const std::string& path)
	{
		tpp::FileMetadata metadata = m_parser.parseMetadata(path);

		// Here, we should have received the parse events and dispatched them accordingly
		return tpp::File(path, metadata);
	}

	void FileReader::onHeaderParsed(tpp::Header* header)
	{
		onHeaderRead.fire(*header);
	}

	void FileReader::onTileParsed(tpp::Tile* tile)
	{
		onTileRead.fire(*tile);
	}

	void FileReader::onObjectParsed(tpp::Object* object)
	{
		onObjectRead.fire(*object);
	}

	void FileReader::onTileSetParsed(tpp::TileSet* set)
	{
		onTileSetRead.fire(*set);
	}

	void FileReader::onTileLayerParsed(tpp::TileLayer* tileLayer)
	{
		onTileLayerRead.fire(*tileLayer);
	}

	void FileReader::onImageLayerParsed(tpp::ImageLayer* imageLayer)
	{
		onImageLayerRead.fire(*imageLayer);
	}

	void FileReader::onObjectLayerParsed(tpp::ObjectLayer* objectLayer)
	{
		onObjectLayerRead.fire(*objectLayer);
	}

	//void FileReader::decompress(tpp::TileLayer& layer)
	//{
	//	// Create a tile outside the loop to speed up things. It will be reused as many times as needed
	//	tpp::Tile tile;
	//	std::string decoded = tpp::Decoder::decode(layer.data.value, layer.data.compression, layer.data.encoding);
	//
	//	for (unsigned int index = 0; index < layer.area; index++)
	//	{
	//		// Reserves 4 bytes for each tile, since encoded tile gids are composed by 4 bytes
	//		unsigned int encodingIndex = index * 4;
	//
	//		// Decodes the gid by shifting left each byte of a gid (see 'Tiled' main page: mapeditor.org)
	//		tile.gid = static_cast<unsigned char>(decoded[encodingIndex])
	//			| static_cast<unsigned char>(decoded[encodingIndex + 1]) << 8
	//			| static_cast<unsigned char>(decoded[encodingIndex + 2]) << 16
	//			| static_cast<unsigned char>(decoded[encodingIndex + 3]) << 24;
	//
	//		// Update the linear 1D position
	//		tile.index = index;
	//
	//		// Get the owner
	//		tile.owner = &layer;
	//
	//		// Reuse the function. Let it set positions, owner, etc
	//		// dispatch(tile);
	//	}
	//}
}