#ifndef LEVELLOADER_H
#define LEVELLOADER_H
#include "fstream"
#include "iostream"

#include "stdlib.h"
#include "ShapeGenerator.h"
#include "ShapeData.h"
#include "Render\Renderer.h"
#include "Level.h"
#include "ExportHeader.h"
using std::ifstream;
using std::ios;
using std::cout;
using std::endl;

class ENGINE_SHARED LevelLoader
{
	LevelLoader(const LevelLoader&);
	LevelLoader& operator = (const LevelLoader&);
	static LevelLoader LevelLoaderInstance; 
public:
	LevelLoader();
	static LevelLoader& getLevelLoaderInstance();
	Level* loadAStar(const char* fileName);
};
#define levelLoader LevelLoader::getLevelLoaderInstance()
#endif