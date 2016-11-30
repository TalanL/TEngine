#ifndef ENGINE_IKEY_MAPPER_H
#define ENGINE_IKEY_MAPPER_H
#include "IKeyMapper.h"
#include "ExportHeader.h"
namespace Input {
	class ENGINE_SHARED IKeyMapper {
	public: 
		virtual int getKeyfor(int action) const = 0;
	};
}
#endif