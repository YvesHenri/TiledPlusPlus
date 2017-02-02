#ifndef TPP_STRUCTURE_FRAME_H
#define TPP_STRUCTURE_FRAME_H

namespace tpp
{
	// Represents the <frame> tag
	struct Frame
	{
		Frame();

		unsigned int duration;
		unsigned int tileGid;
	};
}

#endif