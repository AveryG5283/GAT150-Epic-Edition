#include "Object.h"

namespace minimum
{
	void Object::Read(const json_t& value)
	{
		READ_DATA(value, name)
	}
}