#ifndef SHADERUNIFORMPARAMETER_H
#define SHADERUNIFORMPARAMETER_H
#include "ParameterType.h"

class ShaderUniformParameter
{
public:
	friend class Renderer;
	const char* name;
	ParameterType type;
	const float* value;
	ShaderUniformParameter() {};
	ShaderUniformParameter (char* name, ParameterType type, float* value){
		this->name = name;
		this->type = type;
		this->value = value;
	}
};

#endif