#ifndef RENDERER_H
#define RENDERER_H
#include "Qt\qapplication.h"
#include "QtOpenGL\qglwidget"
#include "glm.hpp"
#include "string.h"
#include "fstream"
#include "Qt\qdebug.h"
#include "gtx\transform.hpp"
#include "Qt\qdebug.h"
#include "iostream"
#include "stdlib.h"
#include "ShapeGenerator.h"
#include "RenderableInfo.h"
#include "ExportHeader.h"

using namespace std;

class ENGINE_SHARED Renderer
{
private:
	static const int numOfBufferInfos = 300;
	static const int numOfGeometryInfos = 100;
	static const int numShaderInfos = 10;
	static const int numRenderInfos = 5000;
	Renderer(const Renderer&);
	Renderer& operator = (const Renderer&);
	static Renderer rendererInstance; 

public:
	static Renderer& getRendererInstance();
	struct BufferInfo
	{
		unsigned int vertexArrayID;
		bool bufferExists;
		GLuint glBufferID;
		GLuint offSet;
		GLuint leftOverSize;
	public:
		BufferInfo()
		{
			leftOverSize = 1000001;
			offSet = 0;
			bufferExists = false;
		}

	}meBufferInfos[numOfBufferInfos];

public:
	GeometryInfo geometryInfos[numOfGeometryInfos];
	ShaderInfo ShaderInfos[numShaderInfos];
	RenderableInfo renderableInfos[numRenderInfos];

	Renderer();
	~Renderer();
	
	//Complete
	GeometryInfo* addGeometry(
		const void* verts,
		GLuint vertexDatasize,
		ushort* indices,
		uint numIndices,
		GLuint indexingMode,
		char* data = 0);

	///Completed
	ShaderInfo* createShaderInfo(
		const char* vertexShaderFileName,
		const char* fragmentShaderfileName);

	std::string readShaderCode(const char* fileName);

	RenderableInfo* addRenderable(
		GeometryInfo* whatGeometry,
		glm::mat4* whereMatrix,
		ShaderInfo* howShaders,
		GLenum mode,
		TexturInfo* tex = NULL);

	void addShaderStreamedParameter(
		GeometryInfo* goeInfoID,
		uint layoutLocation, 
		ParameterType parameterType,
		uint bufferOffset,
		uint bufferStride);

	void addRenderableUniformParameterToRenderable(
		RenderableInfo* renderable,
		ShaderUniformParameter* uniformParameter);

	void addRenderableUniformParameter(
		ShaderInfo* shader,
		const char* name,
		ParameterType parameterType, 
		const float* value);

	TexturInfo* addTexture(const char* fileName);

	void drawRenderable(RenderableInfo* info);

	GeometryInfo* readFile(char* fileName);
	void clearLevel();
};
#define renderer Renderer::getRendererInstance()
#endif