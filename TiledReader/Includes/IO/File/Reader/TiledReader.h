#pragma once

#include <memory>

#include "Event\Event.h"
#include "IO\File\File.h"
#include "IO\File\Parser\IParser.h"
#include "IO\Encoding\Decoder.h"

namespace tpp
{
	class TILEDPP_API TiledReader final
	{
	public:
		TiledReader();
		~TiledReader() = default;

		const tpp::File read(std::string path);

		void setParsingStrategy(tpp::IParser* parser);

		void addFileParsedListener(evt::Delegate<void(tpp::File&)>& delegate);
		void addHeaderParsedListener(evt::Delegate<void(tpp::Header&)>& delegate);
		void addTileSetParsedListener(evt::Delegate<void(tpp::TileSet&)>& delegate);
		void addTileLayerParsedListener(evt::Delegate<void(tpp::TileLayer&)>& delegate);
		void addImageLayerParsedListener(evt::Delegate<void(tpp::ImageLayer&)>& delegate);
		void addObjectLayerParsedListener(evt::Delegate<void(tpp::ObjectLayer&)>& delegate);
		void addTileParsedListener(evt::Delegate<void(tpp::Tile&)>& delegate);
		void addObjectParsedListener(evt::Delegate<void(tpp::Object&)>& delegate);

	private:
		void decompress(tpp::TileLayer& layer);

	private:
		evt::Event<tpp::File&> m_fileParsedEvent;
		evt::Event<tpp::Header&> m_headerParsedEvent;
		evt::Event<tpp::TileSet&> m_tileSetParsedEvent;
		evt::Event<tpp::TileLayer&> m_tileLayerParsedEvent;
		evt::Event<tpp::ImageLayer&> m_imageLayerParsedEvent;
		evt::Event<tpp::ObjectLayer&> m_objectLayerParsedEvent;
		evt::Event<tpp::Tile&> m_tileParsedEvent;
		evt::Event<tpp::Object&> m_objectParsedEvent;

		std::shared_ptr<tpp::IParser> m_parser;
	};
}