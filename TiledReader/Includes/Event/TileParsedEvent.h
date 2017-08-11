#pragma once

#include "Event.h"
#include "IO\File\Structure\Tile.h"

namespace tpp
{
	class TileParsedEvent final : evt::Event<const tpp::Tile&>
	{

	};
}