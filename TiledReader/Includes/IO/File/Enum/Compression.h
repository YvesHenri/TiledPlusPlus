#ifndef TPP_ENUM_COMPRESSION_H
#define TPP_ENUM_COMPRESSION_H

namespace tpp
{
	/// The layer's <data/> compression
	enum class Compression
	{
		None,
		GZIP,
		ZLIB
	};
}

#endif