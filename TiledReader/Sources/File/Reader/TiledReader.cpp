#include "File\Reader\TiledReader.h"
#include "File\Parser\PugiParser.h"

namespace tpp
{
	TiledReader::TiledReader()
	{
		// Sets the default parser
		setParsingStrategy(new tpp::PugiParser);
	}

	TiledReader::~TiledReader()
	{
		// Delete parser pointer only if it is the default one (custom parsers arent deleted).
		if (m_parser != nullptr && dynamic_cast<tpp::PugiParser*>(m_parser))
		{
			delete m_parser;
			m_parser = nullptr;
		}
	}

	void TiledReader::setParsingStrategy(tpp::IParser* parser)
	{
		if (parser != nullptr)
		{
			// Destroy old parser
			if (m_parser)
				delete m_parser;

			// Assign new parser
			m_parser = parser;
		}
	}

	tpp::File TiledReader::read(std::string path) const
	{
		/*tpp::FileMetadata metadata = m_parser->parseMetadata(path);

		for (auto& layer : metadata.layers)
		{
			switch (layer.type)
			{
			case Layer::Tile:
				decompress(layer);
				m_tileLayerParsedEvent.fire(dynamic_cast<tpp::TileLayer&>(layer));
				break;
			case Layer::Image:
				m_imageLayerParsedEvent.fire(dynamic_cast<tpp::ImageLayer&>(layer));
				break;
			case Layer::Object:
				m_objectLayerParsedEvent.fire(dynamic_cast<tpp::ObjectLayer&>(layer));
				break;
			}
		}

		return tpp::File(path, metadata);*/
		return m_parser->parseFile(path);
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