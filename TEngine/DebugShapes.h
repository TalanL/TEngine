#ifndef DEBUGSHAPE_H
#define DEBUGSHAPE_H
#include "QtOpenGL\qglwidget"
#include "Qt\qtimer.h"
#include "glm.hpp"
#include "string.h"
#include "iostream"
#include "stdlib.h"
#include "gtx\transform.hpp"
#include "Qt\qdebug.h"
#include "fstream"
#include "QtGui\qmouseevent"
#include "QtGui\qkeyevent"
#include "ShapeGenerator.h"
#include "ShapeData.h"
#include "Render\ShaderInfo.h"
#include "Render\GeometryInfo.h"
#include "Render\RenderableInfo.h"
#include "Render\TextureInfo.h"
#include "Render\Renderer.h"
#include "debugInfo.h"
#include "ExportHeader.h"
class ENGINE_SHARED DebugShapes
{
	const static int debugSize = 1000; 
	debugInfo debugInfos[debugSize];
	DebugShapes(const DebugShapes&);
	DebugShapes& operator = (const DebugShapes&);
	static DebugShapes debugShapesInstance; 
	Neumont::ShapeGenerator gen;
public:
	static DebugShapes& getDebugShapesInstance();
	debugInfo* AddDebugCube(glm::mat4* modelToWorld, glm::vec4 color, int LifeTime = 999999, bool depthtTest = true);
	debugInfo* AddDebugSphere(glm::mat4* modelToWorld, glm::vec4 color, int LifeTime = 999999, bool depthtTest = true);
	debugInfo* AddDebugPlane(glm::mat4* modelToWorld, glm::vec4 color, int LifeTime = 999999, bool depthtTest = true);
	debugInfo* AddDebugLine(glm::vec3 startpoint, glm::vec3 endpoint, glm::vec4 color, int LifeTime = 999999, bool depthtTest = true);
	void DrawDebug(int dt, ShaderInfo* shader, glm::mat4* veiw);
	DebugShapes();
	~DebugShapes();
	ShaderInfo* debugShader;
private:
	GeometryInfo* cubeGeo;
	GeometryInfo* sphereGeo;
	GeometryInfo* planeGeo;
	GeometryInfo* lineGeo;

};
#define debugShapes DebugShapes::getDebugShapesInstance()
#endif
