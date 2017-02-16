#include <stdio.h>
#include <memory>
#include <vector>

#include "IO\File\Builder\FileReader.h"

void print(tpp::File* file)
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
		}
	}
}

void onHeaderBuilt(const tpp::Header& header)
{
	printf("MEEEEEEEEEEEEEEP \n");
}

void test()
{
	tpp::FileReader reader;

	try
	{
		reader.onHeaderBuilt.attach(evt::Delegate<void(const tpp::Header&)>(&onHeaderBuilt));

		tpp::File meep = reader.read("Resources//Maps//attr.tmx");
		tpp::File* file; // = &reader.read("Resources//Maps//attr.tmx"); // Error

		file = &meep; // Ok

		print(&meep);
		//print(file);
	}
	catch (...)
	{
		printf("Error!\n");
	}
}

void paths()
{
	tpp::Path invalidPath = "D://Documents//Meepz//";

	printf("File Name: %s \n", invalidPath.getFileName().c_str());
	printf("File Full name: %s \n", invalidPath.getFileFullName().c_str());
	printf("File Path: %s \n", invalidPath.getFilePath().c_str());
	printf("File Full path: %s \n", invalidPath.getFileFullPath().c_str());
	printf("File Extension: %s \n", invalidPath.getFileExtension().c_str());
	printf("-------------------------------------------- \n");

	tpp::Path validPath("D://Documents//Diablo III//");

	printf("File Name: %s \n", validPath.getFileName().c_str());
	printf("File Full name: %s \n", validPath.getFileFullName().c_str());
	printf("File Path: %s \n", validPath.getFilePath().c_str());
	printf("File Full path: %s \n", validPath.getFileFullPath().c_str());
	printf("File Extension: %s \n", validPath.getFileExtension().c_str());
	printf("-------------------------------------------- \n");

	tpp::Path invalidFile("D://Documents//Diablo III//whatever.meep");

	printf("File Name: %s \n", invalidFile.getFileName().c_str());
	printf("File Full name: %s \n", invalidFile.getFileFullName().c_str());
	printf("File Path: %s \n", invalidFile.getFilePath().c_str());
	printf("File Full invalidFile: %s \n", invalidFile.getFileFullPath().c_str());
	printf("File Extension: %s \n", invalidFile.getFileExtension().c_str());
	printf("-------------------------------------------- \n");

	tpp::Path invalidFileExtensionless("D://Documents//Diablo III//whatever");

	printf("File Name: %s \n", invalidFileExtensionless.getFileName().c_str());
	printf("File Full name: %s \n", invalidFileExtensionless.getFileFullName().c_str());
	printf("File Path: %s \n", invalidFileExtensionless.getFilePath().c_str());
	printf("File Full path: %s \n", invalidFileExtensionless.getFileFullPath().c_str());
	printf("File Extension: %s \n", invalidFileExtensionless.getFileExtension().c_str());
	printf("-------------------------------------------- \n");

	tpp::Path validFile("D://Documents//Diablo III//D3Prefs.txt");

	printf("File Name: %s \n", validFile.getFileName().c_str());
	printf("File Full name: %s \n", validFile.getFileFullName().c_str());
	printf("File Path: %s \n", validFile.getFilePath().c_str());
	printf("File Full validFile: %s \n", validFile.getFileFullPath().c_str());
	printf("File Extension: %s \n", validFile.getFileExtension().c_str());
	printf("-------------------------------------------- \n");

	tpp::Path validFileExtensionless("D://Documents//Diablo III//D3Prefs");

	printf("File Name: %s \n", validFileExtensionless.getFileName().c_str());
	printf("File Full name: %s \n", validFileExtensionless.getFileFullName().c_str());
	printf("File Path: %s \n", validFileExtensionless.getFilePath().c_str());
	printf("File Full validFile: %s \n", validFileExtensionless.getFileFullPath().c_str());
	printf("File Extension: %s \n", validFileExtensionless.getFileExtension().c_str());
	printf("-------------------------------------------- \n");
}

int main()
{
	{
		//paths();
		test();
	}

	//tpp::File file;
	//
	//{
	//	tpp::TiledReader reader;
	//	tpp::File temp = reader.read("Resources//Maps//attr.tmx");
	//	
	//	file = std::move(temp);
	//	file = std::move(reader.read("Resources//Maps//attr.tmx"));
	//}

	return getchar();
}
