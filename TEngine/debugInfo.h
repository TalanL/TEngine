#ifndef DEBUGINFO_H
#define DEBUGINFO_H
class debugInfo
{
public:
	debugInfo(){}
	glm::vec4 color;
	int lifeRemaining;
	bool depthTest;
	RenderableInfo myRender;
	glm::mat4 modelToWorld;
};
#endif