#include <Gl\glew.h>
#include "DebugShapes.h"


DebugShapes DebugShapes::debugShapesInstance;
DebugShapes& DebugShapes::getDebugShapesInstance()
{
	return debugShapesInstance;
}

DebugShapes::DebugShapes() {}

DebugShapes::~DebugShapes() {}

static int currentInfo = 0;

debugInfo* DebugShapes::AddDebugCube(glm::mat4* modelToWorld, glm::vec4 color, int LifeTime, bool depthtTest)
{
	if(debugShader == NULL)
	{
		debugShader = renderer.createShaderInfo("DebugVertexShader.glsl", "DebugFragmentShader.glsl");
	}
	if(cubeGeo == NULL)
	{
		Neumont::ShapeData cube = gen.makeCube();
		cubeGeo = renderer.addGeometry(cube.verts, cube.vertexBufferSize(), cube.indices, cube.numIndices, GL_TRIANGLES);
	}
	GLuint cubeByteOffset = cubeGeo->offsetInBuffer;
	renderer.addShaderStreamedParameter(cubeGeo, 0, PT_VEC3, Neumont::Vertex::STRIDE, (cubeByteOffset + Neumont::Vertex::POSITION_OFFSET));
	debugInfos[currentInfo].color = color;
	debugInfos[currentInfo].depthTest = depthtTest;
	debugInfos[currentInfo].lifeRemaining = LifeTime;
	debugInfos[currentInfo].myRender = *(renderer.addRenderable(cubeGeo, modelToWorld, debugShader, GL_TRIANGLES));
	debugInfos[currentInfo].myRender.textureID = NULL;
	debugInfos[currentInfo].modelToWorld = *modelToWorld;
	currentInfo ++;
	return &debugInfos[currentInfo-1];
}

debugInfo* DebugShapes::AddDebugSphere(glm::mat4* modelToWorld, glm::vec4 color, int LifeTime, bool depthtTest)
{
	if(debugShader == NULL)
	{
		debugShader = renderer.createShaderInfo("DebugVertexShader.glsl", "DebugFragmentShader.glsl");
	}
	if(sphereGeo == NULL)
	{
		Neumont::ShapeData sphere = gen.makeSphere(10);
		sphereGeo = renderer.addGeometry(sphere.verts, sphere.vertexBufferSize(), sphere.indices, sphere.numIndices, GL_TRIANGLES);
	}
	GLuint sphereByteOffset = sphereGeo->offsetInBuffer;
	renderer.addShaderStreamedParameter(sphereGeo, 0, PT_VEC3, Neumont::Vertex::STRIDE, (sphereByteOffset + Neumont::Vertex::POSITION_OFFSET));
	debugInfos[currentInfo].color = color;
	debugInfos[currentInfo].depthTest = depthtTest;
	debugInfos[currentInfo].lifeRemaining = LifeTime;
	debugInfos[currentInfo].myRender = *(renderer.addRenderable(sphereGeo, modelToWorld, debugShader,  GL_TRIANGLES));
	debugInfos[currentInfo].myRender.textureID = NULL;
	debugInfos[currentInfo].modelToWorld = *modelToWorld;
	currentInfo ++;
	return &debugInfos[currentInfo-1];
}


debugInfo* DebugShapes::AddDebugPlane(glm::mat4* modelToWorld, glm::vec4 color, int LifeTime, bool depthtTest)
{
	if(debugShader == NULL)
	{
		debugShader = renderer.createShaderInfo("DebugVertexShader.glsl", "DebugFragmentShader.glsl");
	}
	if(planeGeo == NULL)
	{
		Neumont::ShapeData plane = gen.makePlane(10);
		planeGeo = renderer.addGeometry(plane.verts, plane.vertexBufferSize(), plane.indices, plane.numIndices, GL_TRIANGLES);
	}
	GLuint planeByteOffset = planeGeo->offsetInBuffer;
	renderer.addShaderStreamedParameter(planeGeo, 0, PT_VEC3, Neumont::Vertex::STRIDE, (planeByteOffset + Neumont::Vertex::POSITION_OFFSET));
	debugInfos[currentInfo].color = color;
	debugInfos[currentInfo].depthTest = depthtTest;
	debugInfos[currentInfo].lifeRemaining = LifeTime;
	debugInfos[currentInfo].myRender = *(renderer.addRenderable(planeGeo, modelToWorld, debugShader,  GL_TRIANGLES));
	debugInfos[currentInfo].myRender.textureID = NULL;
	debugInfos[currentInfo].modelToWorld = *modelToWorld;
	currentInfo ++;
	return &debugInfos[currentInfo-1];
}


void DebugShapes::DrawDebug(int dt, ShaderInfo* shader, glm::mat4* veiw)
{	
	if(debugShader != NULL)
	{
		glUseProgram(debugShader->programID);
	}

	for( int i = 0; i < currentInfo; i++)
	{
		glm::mat4 transformationFull = *veiw * debugInfos[i].modelToWorld;

		if(debugInfos[i].lifeRemaining > 0)
		{
			if(!debugInfos[i].depthTest)
			{
				glDisable(GL_DEPTH_TEST);
				renderer.addRenderableUniformParameter(shader, "dominateColor",	PT_VEC4,  &debugInfos[i].color[0]);
				renderer.addRenderableUniformParameter(shader, "transformation",PT_MAT4,  &transformationFull[0][0]);
				renderer.drawRenderable(&debugInfos[i].myRender);
			}
			else
			{
				glEnable(GL_DEPTH_TEST);
				renderer.addRenderableUniformParameter(shader, "dominateColor",	PT_VEC4,  &debugInfos[i].color[0]);
				renderer.addRenderableUniformParameter(shader, "transformation",PT_MAT4, &transformationFull[0][0]);
				renderer.drawRenderable(&debugInfos[i].myRender);
			}
			debugInfos[i].lifeRemaining = debugInfos[i].lifeRemaining - dt;
		}
	}
}