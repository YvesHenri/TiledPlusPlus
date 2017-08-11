#pragma once

#include <memory>

#include "IO\File\File.h"
#include "IO\File\Enum\Flip.h"
#include "IO\File\Builder\FileMetadataParser.h"
#include "IO\File\Builder\FileReaderSettings.h"
#include "IO\Compression\Decoder.h"

namespace tpp
{
	// Reads a TMX file. This behaves like the Director in the builder pattern.
	class TILEDPP_API FileReader final
	{
	public:
		FileReader(const tpp::FileReaderSettings& settings = tpp::FileReaderSettings());

		tpp::File read(const tpp::Path& path);
		tpp::File read(const std::string& path);

	private:
		void onTileParsed(tpp::Tile*);
		void onObjectParsed(tpp::Object*);
		void onHeaderParsed(tpp::Header*);
		void onTileSetParsed(tpp::TileSet*);
		void onTileLayerParsed(tpp::TileLayer*);
		void onImageLayerParsed(tpp::ImageLayer*);
		void onObjectLayerParsed(tpp::ObjectLayer*);

	public:
		evt::Event<const tpp::Tile&> onTileRead;
		evt::Event<const tpp::Object&> onObjectRead;
		evt::Event<const tpp::Header&> onHeaderRead;
		evt::Event<const tpp::TileSet&> onTileSetRead;
		evt::Event<const tpp::TileLayer&> onTileLayerRead;
		evt::Event<const tpp::ImageLayer&> onImageLayerRead;
		evt::Event<const tpp::ObjectLayer&> onObjectLayerRead;

	private:
		tpp::FileMetadataParser m_parser;
		tpp::FileReaderSettings m_settings;
	};
}