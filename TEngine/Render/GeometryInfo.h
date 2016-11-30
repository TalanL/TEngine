#ifndef GEOMETRYINFO_H
#define GEOMETRYINFO_H
#include "glm.hpp"
#include "miscTypeDef.h"
class GeometryInfo
{
public:
	uint vertexArrayID; 
	uint numIndices;
	uint indexOffset;
	uint indexingMode;
	uint bufferID;
	uint offsetInBuffer;
	uint numVerts;
	char* data;
};
#endif