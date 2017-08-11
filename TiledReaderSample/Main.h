#pragma once

#include <IO\File\Builder\FileReader.h>

void read(const std::string& path, bool print, bool objects, bool tiles);
void onObjectRead(const tpp::Object& object);
void onTileRead(const tpp::Tile& tile);
void printFileData(tpp::File* file);