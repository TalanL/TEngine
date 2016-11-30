#include "GL\glew.h"
#include "Renderer.h"
Renderer Renderer::rendererInstance;
Renderer& Renderer::getRendererInstance()
{
	return rendererInstance;
}


static int currentBufferInfo;
static int currentGeometryInfos;
static int currentShadersInfos;
static int currentRenderableInfos;

Renderer::Renderer()
{}


Renderer::~Renderer()
{}


GeometryInfo* Renderer::addGeometry(
	const void* verts,
	GLuint vertexDatasize,
	ushort* indices,
	uint numIndices,
	GLuint indexingMode,
	char* data)
{
	
	GeometryInfo& returnValue = geometryInfos[currentGeometryInfos++];
	bool foundBuffer = false;
	GLuint indexDataSize = numIndices * sizeof(ushort);

	for(int i = 0; i < numOfBufferInfos && !foundBuffer; i++)
	{
		if(meBufferInfos[i].leftOverSize > vertexDatasize + indexDataSize)
		{
			foundBuffer = true;
			if(!meBufferInfos[i].bufferExists)
			{
				glGenBuffers(1, &meBufferInfos[i].glBufferID);
				glBindBuffer(GL_ARRAY_BUFFER, meBufferInfos[i].glBufferID);
				glBufferData(GL_ARRAY_BUFFER,  1000001, 0, GL_STATIC_DRAW);
				meBufferInfos[i].bufferExists = true;
			}
			returnValue.offsetInBuffer = meBufferInfos[i].offSet;
			glGenVertexArrays(1, &meBufferInfos[i].vertexArrayID);
			glBindVertexArray(meBufferInfos[i].vertexArrayID);
				
			
			glBufferSubData(GL_ARRAY_BUFFER, meBufferInfos[i].offSet, vertexDatasize,verts);
			meBufferInfos[i].offSet+= vertexDatasize;
			glBufferSubData(GL_ARRAY_BUFFER, meBufferInfos[i].offSet, indexDataSize, indices);
			meBufferInfos[i].offSet += indexDataSize;


			glBindBuffer(GL_ARRAY_BUFFER, meBufferInfos[i].glBufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meBufferInfos[i].glBufferID);

			returnValue.vertexArrayID = meBufferInfos[i].vertexArrayID;
			returnValue.numIndices = numIndices;
			returnValue.indexOffset = meBufferInfos[i].offSet - indexDataSize;
			returnValue.indexingMode = indexingMode;
			returnValue.bufferID = meBufferInfos[i].glBufferID;
			returnValue.numVerts = vertexDatasize/sizeof(Neumont::Vertex);
			returnValue.data = data;
			meBufferInfos[i].leftOverSize = meBufferInfos[i].leftOverSize - vertexDatasize;

		}
	}
	return &returnValue;
}

ShaderInfo* Renderer::createShaderInfo(
	const char* vertexShaderFileName,
	const char* fragmentShaderfileName)
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const char* adaptor[1];
	std::string temp =  readShaderCode(vertexShaderFileName);
	adaptor[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adaptor, 0);
	temp = readShaderCode(fragmentShaderfileName);
	adaptor[0] = temp.c_str();
	glShaderSource(fragShaderID, 1, adaptor, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragShaderID);

	GLint compileStatus;
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &compileStatus);
	if(compileStatus != GL_TRUE)
	{
		GLint logLength;
		glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &logLength);
		char * buffer = new char[logLength];
		GLsizei bitbucket;
		glGetShaderInfoLog(vertexShaderID, logLength, &bitbucket, buffer);
		qDebug() << buffer;
		delete [] buffer;
	}

	glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &compileStatus);
	if(compileStatus != GL_TRUE)
	{
		GLint logLength;
		glGetShaderiv(fragShaderID, GL_INFO_LOG_LENGTH, &logLength);
		char * buffer = new char[logLength];
		GLsizei bitbucket;
		glGetShaderInfoLog(fragShaderID, logLength, &bitbucket, buffer);
		qDebug() << buffer;
		delete [] buffer;
	}

	ShaderInfo& programID = ShaderInfos[0];
	programID.programID = glCreateProgram();
	glAttachShader(programID.programID, vertexShaderID);
	glAttachShader(programID.programID, fragShaderID);

	glLinkProgram(programID.programID);
	return &programID;
}

// pull the next shader info.
std::string Renderer::readShaderCode(const char* fileName)
{
	std::ifstream meInput(fileName);
	if(! meInput.good())
	{
	}
	return std::string(
		std::istreambuf_iterator<char>(meInput),
		std::istreambuf_iterator<char>());
}


RenderableInfo* Renderer::addRenderable(
	GeometryInfo* whatGeometry,
	glm::mat4* whereMatrix,
	ShaderInfo* howShaders,
	GLenum mode,
	TexturInfo* tex)
{

	RenderableInfo* information = &renderableInfos[currentRenderableInfos++];

	information->whatGeometry = whatGeometry;
	information->howShaders = howShaders;
	information->whereMatrix = whereMatrix;
	information->mode = mode;
	information->textureID = tex;
	return information;
}


void Renderer::addShaderStreamedParameter(
	GeometryInfo* goeInfoID,
	uint layoutLocation, 
	ParameterType parameterType,
	uint bufferStride, 
	uint bufferOffset)
{
	glBindVertexArray(goeInfoID->vertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, goeInfoID->bufferID);
	glEnableVertexAttribArray(layoutLocation);
	glVertexAttribPointer(layoutLocation, (parameterType/sizeof(float)), GL_FLOAT, GL_FALSE, bufferStride, (void*)bufferOffset);
}


void Renderer::addRenderableUniformParameter(
	ShaderInfo* shader,
	const char* name,
	ParameterType parameterType, 
	const float* value)
{
	GLuint uniformTargetLocation = glGetUniformLocation(shader->programID, name);
	if( parameterType == PT_FLOAT)
	{
		glUniform1f(uniformTargetLocation, *value);
	}

	else if( parameterType == PT_VEC2)
	{
		glUniform2fv(uniformTargetLocation, 1, value);
	}

	else if( parameterType == PT_VEC3)
	{
		glUniform3fv(uniformTargetLocation, 1, value);
	}

	else if( parameterType == PT_VEC4)
	{
		glUniform4fv(uniformTargetLocation, 1, value);
	}

	else if( parameterType == PT_MAT3)
	{
		glUniformMatrix3fv(uniformTargetLocation, 1, GL_FALSE, value);
	}

	else if( parameterType == PT_MAT4)
	{
		glUniformMatrix4fv(uniformTargetLocation, 1,GL_FALSE, value);
	}
}

TexturInfo* Renderer::addTexture(const char* fileName)
{
	TexturInfo* theTex = new TexturInfo;
	static GLint currentindex = 0;
	GLuint textureID;
	glActiveTexture(GL_TEXTURE0 + currentindex);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	QImage image = QImage(fileName);
	image = QGLWidget::convertToGLFormat(image);
	int textureHeight = image.height();
	int textureWidth = image.width();
	uchar* pixelPointer = image.bits();

	// jpg GL_RGBA
	//bitmap GL_BGRA
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0,  GL_RGBA, GL_UNSIGNED_BYTE, pixelPointer);

	//setting for the way your texturing 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//gl liner or gl nearest
	//liner = blurs it all together 
	//nearest = 8 bit junk
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	theTex->textureID = textureID;
	return theTex;
};

void Renderer::drawRenderable(RenderableInfo* info)
{
	if(info->textureID != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, info->textureID->textureID);
	}
	for(int i = 0; i < info->numberOfParametersUsed; i++){
		if(info->uniformParameters[i] != NULL)
		{
			addRenderableUniformParameter(info->howShaders, info->uniformParameters[i]->name, info->uniformParameters[i]->type, info->uniformParameters[i]->value);
		}
	}
	GLuint samplerLocl = glGetUniformLocation(info->howShaders->programID, "tex");
	glUniform1i(samplerLocl, 0);
	glBindVertexArray(info->whatGeometry->vertexArrayID);
	glDrawElements(info->mode, info->whatGeometry->numIndices, GL_UNSIGNED_SHORT, (void*)info->whatGeometry->indexOffset);
}

GeometryInfo* Renderer::readFile(char* fileName)
{
	ifstream myfile;
	myfile.open(fileName, ios::in | ios::binary);
	if(myfile.fail())
	{
		cout <<"FAIL"<<endl;
	}
	int* header = new int[2];
	header[0] = 0;
	header[1] = 0;
	//myfile.read( (char*)header, 8 );
	myfile.read(reinterpret_cast<char*>(header), 8);
	int vertexSize = sizeof(Neumont::Vertex) * header[0];
	int indexSize = sizeof(ushort) * header[1];
	char* data = new char[vertexSize + indexSize];
	myfile.read(reinterpret_cast<char*>(data), vertexSize + indexSize);
	delete header;
	return addGeometry(reinterpret_cast<Neumont::Vertex*>(data), vertexSize, reinterpret_cast<ushort*>(data + vertexSize), indexSize/2, GL_TRIANGLES, data);
}

void Renderer::addRenderableUniformParameterToRenderable(RenderableInfo* renderable, ShaderUniformParameter* uniformParameter)
{
	if(renderable->numberOfParametersUsed < renderable->numberOfParameters){
		renderable->uniformParameters[renderable->numberOfParametersUsed++] = uniformParameter;
	}
}
