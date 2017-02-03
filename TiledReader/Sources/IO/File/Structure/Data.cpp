#include "IO\File\Structure\Data.h"

namespace tpp
{
	Data::Data()
		: encoding(Encoding::None)
		, compression(Compression::None)
		, value("")
	{}
}