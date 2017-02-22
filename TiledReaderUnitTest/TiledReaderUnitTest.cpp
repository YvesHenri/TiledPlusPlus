#include "TiledReaderUnitTest.h"

int main()
{
	read("Resources//Maps//attr018.tmx", false, false, false);
	return getchar();
}

void read(const std::string& path, bool print, bool objects, bool tiles)
{
	tpp::File file;

	{
		tpp::FileReaderSettings settings;

		settings.storeTilesAfterRead = true; // Setting to false will potentially speed things up
		settings.skipHandlingBlankTiles = true; // Setting to true will slightly speed things up
		settings.skipHandlingHiddenObjects = false; // Setting to true will slightly speed things up

		tpp::FileReader reader(settings);

		if (objects)
			reader.onObjectRead.attach(evt::Delegate<void(const tpp::Object&)>(&onObjectRead));

		if (tiles)
			reader.onTileRead.attach(evt::Delegate<void(const tpp::Tile&)>(&onTileRead));

		try
		{
			TIME_PROFILER("Reading file");
			file = std::move(reader.read(path));
		}
		catch (const std::runtime_error& e)
		{
			printf("Runtime error: %s!\n", e.what());
		}
		catch (...)
		{
			printf("Unknown error!\n");
		}
	}

	if (print)
		printFileData(&file);
}

void onTileRead(const tpp::Tile& tile)
{
	printf("[onTileRead] Tile of GID %d has size %dx%d and is at (%d, %d) \n", tile.gid, tile.width, tile.height, tile.x, tile.y);
}

void onObjectRead(const tpp::Object& object)
{
	printf("[onObjectRead] Object \'%s\' (%d) has %d points and is at (%d, %d) \n", object.name.c_str(), object.id, object.points.size(), object.x, object.y);
}

void printFileData(tpp::File* file)
{
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ \n");
	printf("@@@@@@@@@@@@@@@@@    HEADER     @@@@@@@@@@@@@@ \n");
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ \n");
	printf("Analyzing header for file \'%s\'...\n", file->getPath().getFileName().c_str());
	printf("Map is %dx%d long, with %dx%d tiles. \n",
		file->getHeader().width, file->getHeader().height, file->getHeader().tileWidth, file->getHeader().tileHeight);
	printf("It contains %d tile sets, %d image layers, %d tile layers and %d object layers (Total layers: %d) \n",
		file->getHeader().tileSetsCount, file->getHeader().imageLayersCount, file->getHeader().tileLayersCount, file->getHeader().objectLayersCount,
		file->getHeader().imageLayersCount + file->getHeader().tileLayersCount + file->getHeader().objectLayersCount);

	// Tile sets
	if (!file->getTileSets().empty())
	{
		printf("\n");
		printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ \n");
		printf("@@@@@@@@@@@@@@@@@    TILE SET    @@@@@@@@@@@@@@ \n");
		printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ \n");
		for (const auto& set : file->getTileSets())
		{
			printf("Tile set \'%s\" has %d tiles of size %dx%d (First: %d, Last: %d) \n",
				set.name.c_str(), set.tilesCount, set.tileWidth, set.tileHeight, set.firstTileId, set.lastTileId
			);
			printf("It uses the texture at \'%s\' \n", set.image.source.c_str());
			printf("---------------------------------------------- \n");
		}
	}

	// Layers
	if (!file->getLayers().empty())
	{
		for (const auto& layer : file->getLayers())
		{
			printf("\n");
			printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ \n");
			if (layer->material == tpp::Material::Image)
				printf("@@@@@@@@@@@@@@@@   IMAGE LAYER   @@@@@@@@@@@@@ \n");
			else if (layer->material == tpp::Material::Object)
				printf("@@@@@@@@@@@@@@@@  OBJECT LAYER   @@@@@@@@@@@@@ \n");
			else if (layer->material == tpp::Material::Tile)
				printf("@@@@@@@@@@@@@@@@   TILE LAYER    @@@@@@@@@@@@@ \n");
			printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ \n");

			printf("Layer \'%s\' is located at (%d, %d) \n", layer->name.c_str(), layer->x, layer->y);

			if (layer->material == tpp::Material::Object)
			{
				tpp::ObjectLayer* objectLayer = static_cast<tpp::ObjectLayer*>(layer.get());

				for (const auto& object : objectLayer->objects)
				{
					printf("Object of ID %d belongs to group \'%s\' \n", object.second.id, object.second.owner->name.c_str());
				}
			}
			else if (layer->material == tpp::Material::Tile)
			{
				auto tileLayer = static_cast<tpp::TileLayer*>(layer.get());

				for (const auto& tile : tileLayer->tiles)
				{
					if (tile.isFlippedDiagonally)
						printf("isFlippedDiagonally (%d) \n", tile.gid);
					if (tile.isFlippedVertically)
						printf("isFlippedVertically (%d) \n", tile.gid);
					if (tile.isFlippedHorizontally)
						printf("isFlippedHorizontally (%d) \n", tile.gid);
					if (tile.isFlippedDiagonally || tile.isFlippedHorizontally || tile.isFlippedVertically)
						printf("----------------- \n");
				}
			}
		}
	}
}