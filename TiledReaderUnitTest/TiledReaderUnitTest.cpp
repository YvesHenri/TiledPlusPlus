#include <stdio.h>

//#include "IO\File\Reader\TiledReader.h"
#include "Event\Event.h"

int main()
{
	evt::Event<int> header;

	//tpp::TiledReader reader;

	//try
	//{
	//	tpp::File result = reader.read("Resources//Maps//attr.tmx");

	//	try {
	//		printf("Name: %s \n", result.getName().c_str());
	//		printf("Width: %d \n", result.getHeader().width);
	//		printf("Height: %d \n", result.getHeader().height);
	//		printf("Orientation: %d \n", result.getHeader().orientation);

	//		// Object layers
	//		printf("Checking all pointers...\n");
	//		for (const auto& group : result.getObjectLayers())
	//		{
	//			printf("Analizing group \'%s\' \n", group.name.c_str());
	//			for (const auto& object : group.objects)
	//			{
	//				printf("Object of ID %d belongs to group \'%s\' \n", object.second.id, object.second.owner->name.c_str());
	//			}
	//		}
	//	}
	//	catch (const std::exception& e) {
	//		printf("Erro: %s \n", e.what());
	//	}
	//}
	//catch (...)
	//{
	//	printf("Error!\n");
	//}

	return getchar();
}
