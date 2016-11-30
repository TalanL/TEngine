#ifndef RENDERER_COMPONENT_H
#define RENDERER_COMPONENT_H
#include "GameObject\Component.h"
#include "Render\RenderableInfo.h"
#include "glm.hpp"
#include "gtx\transform.hpp"
#include "ExportHeader.h"
namespace GameObjects
{
	class ENGINE_SHARED RendererComponent : public Component
	{
		glm::mat4 whereMatrix;
		glm::mat4* worldToProjectionMatrix;
		RenderableInfo* renderableInfo;
		vec3* scale;
	public:
		void setData(RenderableInfo* RenderableInfo, glm::mat4* worldToProjectionMatrix, vec3* scale);
		void update();
	};
}
#endif