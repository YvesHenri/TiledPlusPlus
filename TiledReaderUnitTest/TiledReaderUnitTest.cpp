#include <stdio.h>

#include "File\Reader\TiledReader.h"

int main()
{
	tpp::TiledReader reader;

	try
	{
		tpp::File result = reader.read("Resources//Maps//attr.tmx");

		printf("Name: %s \n", result.getName().c_str());
		printf("Width: %d \n", result.getHeader().width);
		printf("Height: %d \n", result.getHeader().height);
		printf("Orientation: %d \n", result.getHeader().orientation);
	}
	catch (...)
	{
		printf("Error!\n");
	}

	return getchar();
}
