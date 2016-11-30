#ifndef RENDERABLEINFO_H
#define RENDERABLEINFO_H
#include "glm.hpp"
#include "GeometryInfo.h"
#include "ShaderInfo.h"
#include "ShaderUniformParameter.h"
#include "TextureInfo.h"

class RenderableInfo
{
public:
	static const int numberOfParameters = 10;
	GeometryInfo* whatGeometry;
	glm::mat4* whereMatrix;
	ShaderInfo* howShaders;
	bool visible;
	TexturInfo* textureID;
	TexturInfo* noramlID;
	unsigned int mode;
	int numberOfParametersUsed;
	ShaderUniformParameter* uniformParameters[numberOfParameters];
	RenderableInfo()
	{
		visible = true;
		numberOfParametersUsed = 0;

	}
};

#endif
