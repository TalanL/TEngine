#include "RendererComponent.h"
#include "Render\Renderer.h"

namespace GameObjects
{

	void RendererComponent::setData(RenderableInfo* renderableInfo, glm::mat4* worldToProjectionMatrix, vec3* scale){
		this->renderableInfo = renderableInfo;
		this->worldToProjectionMatrix = worldToProjectionMatrix;
		this->scale = scale;
	}

	void RendererComponent::update() {
		whereMatrix = (glm::rotate(parent->orientation, vec3(0.0f,1.0f,0.0f)) *
						glm::translate(parent->position) *
						glm::scale((*scale)));
		renderableInfo->whereMatrix = &whereMatrix;
		glm::mat4 transFormation = *renderableInfo->whereMatrix;
		transFormation = *worldToProjectionMatrix * transFormation;
		renderer.addRenderableUniformParameter(renderableInfo->howShaders, "transformation", PT_MAT4, &transFormation[0][0]);
		renderer.addRenderableUniformParameter(renderableInfo->howShaders, "modelToWorld", PT_MAT4, &whereMatrix[0][0]);
		renderer.drawRenderable(renderableInfo);
	}
}