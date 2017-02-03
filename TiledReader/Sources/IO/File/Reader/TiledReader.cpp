#include "IO\File\Reader\TiledReader.h"
#include "IO\File\Parser\PugiParser.h"

namespace tpp
{
	TiledReader::TiledReader()
	{
		setParsingStrategy(new tpp::PugiParser);
	}

	void TiledReader::setParsingStrategy(tpp::IParser* parser)
	{
		m_parser.reset(parser);
	}

	const tpp::File TiledReader::read(std::string path)
	{
		tpp::FileMetadata metadata = m_parser->parseMetadata(path);

		for (tpp::TileLayer& layer : metadata.tileLayers)
		{
			// Since encoding applies to all the layers, if one isnt encoded, none will be
			if (layer.data.encoding != tpp::Encoding::Base64)
				break;

			// Layers are compressed. Decompress it
			decompress(layer);
		}

		return tpp::File(path, metadata);
	}

	void TiledReader::decompress(tpp::TileLayer& layer)
	{
		// Create a tile outside the loop to speed up things. It will be reused as many times as needed
		tpp::Tile tile;
		std::string decoded = ""; // tpp::Decoder::decode(layer.data);

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

	void TiledReader::addFileParsedListener(evt::Delegate<void(tpp::File&)>& delegate)
	{
		m_fileParsedEvent.attach(delegate);
	}

	void TiledReader::addHeaderParsedListener(evt::Delegate<void(tpp::Header&)>& delegate)
	{
		m_headerParsedEvent.attach(delegate);
	}

	void TiledReader::addTileParsedListener(evt::Delegate<void(tpp::Tile&)>& delegate)
	{
		m_tileParsedEvent.attach(delegate);
	}

	void TiledReader::addObjectParsedListener(evt::Delegate<void(tpp::Object&)>& delegate)
	{
		m_objectParsedEvent.attach(delegate);
	}

	void TiledReader::addTileSetParsedListener(evt::Delegate<void(tpp::TileSet&)>& delegate)
	{
		m_tileSetParsedEvent.attach(delegate);
	}

	void TiledReader::addTileLayerParsedListener(evt::Delegate<void(tpp::TileLayer&)>& delegate)
	{
		m_tileLayerParsedEvent.attach(delegate);
	}

	void TiledReader::addImageLayerParsedListener(evt::Delegate<void(tpp::ImageLayer&)>& delegate)
	{
		m_imageLayerParsedEvent.attach(delegate);
	}

	void TiledReader::addObjectLayerParsedListener(evt::Delegate<void(tpp::ObjectLayer&)>& delegate)
	{
		m_objectLayerParsedEvent.attach(delegate);
	}
}