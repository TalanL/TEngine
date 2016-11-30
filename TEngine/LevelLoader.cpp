#include "LevelLoader.h"

LevelLoader LevelLoader::LevelLoaderInstance;
LevelLoader& LevelLoader::getLevelLoaderInstance()
{
	return LevelLoaderInstance;
}

LevelLoader::LevelLoader(){}

Level* LevelLoader::loadAStar(const char* fileName)
{
	Level* level = new Level();
	ifstream in(fileName, ios::binary | ios::in);
	if(in.fail())
	{
		cout <<fileName<<endl;
	}
	int* header = new int[3];
	unsigned int sizeOfHeader = sizeof(header) * 3;
	header[0] = 0;
	in.read(reinterpret_cast<char*>(header),12);
	unsigned int sizeOfvertexData = sizeof(Neumont::Vertex) * header[0];
	unsigned int sizeOfIndextDara = sizeof(ushort) * header[1];
	unsigned int totalGeoSize = sizeOfvertexData + sizeOfIndextDara;
	//unsigned int sizeOfNode = sizeof(GameNode);
	//unsigned int sizeOfAllNode = sizeOfNode * header[2];
	//unsigned int connectionStart = sizeOfHeader + sizeOfAllNode + totalGeoSize;

	//unsigned int sizeOfConnection = sizeof(GameConnection);

	in.seekg(0, ios::end); //pointer at the end
	size_t numBytes = in.tellg(); //why byte the pointer is at. The pointer is at the end in this case.
	in.seekg(0, ios::beg);//points the pointer back to the start.

	char* buf = new char[numBytes]; //All information in the exact size in the file.
	in.read(buf, numBytes); //Read entier file in this array.
	in.close(); //closes.

	int numNodes = header[2];
	GameNode* gNodes = new GameNode[numNodes];
	char* data =  reinterpret_cast<char*>(buf + sizeOfHeader);

	level->levelGeo = (renderer.addGeometry(reinterpret_cast<Neumont::Vertex*>(data),
		sizeOfvertexData,
		reinterpret_cast<ushort*>(data + sizeOfvertexData),
		sizeOfIndextDara,
		GL_TRIANGLES,
		data));
	unsigned int byteoffset = sizeOfHeader + totalGeoSize;
	unsigned int* connectionFileOffsets = new unsigned int[numNodes];

	for(int i = 0; i < numNodes; i++)
	{
		cout << "Current Node Data:" << i << "------------------------------------"<< endl;
		gNodes[i].postion.x = *reinterpret_cast<float*>((buf+byteoffset));
		byteoffset = byteoffset + 4;
		gNodes[i].postion.y = *reinterpret_cast<float*>((buf+byteoffset));
		byteoffset  = byteoffset + 4;
		gNodes[i].postion.z = *reinterpret_cast<float*>((buf+byteoffset));
		byteoffset  = byteoffset + 4;
		gNodes[i].numConnections = *reinterpret_cast<int*>((buf+byteoffset));
		cout << "NumConnections:" << gNodes[i].numConnections << endl;
		byteoffset  = byteoffset + 4; 
		connectionFileOffsets[i] = *reinterpret_cast<unsigned int*>((buf+byteoffset));
		byteoffset = byteoffset + 4;
		cout << "Node: " << i << " Address" << &gNodes[i]<< endl;
	}

	for(int i = 0; i < numNodes; i ++)
	{	
		cout << "Current Node connection start:" << i << "-------------------------------------------------------"<< endl;
		if(!(gNodes[i].numConnections <= 0))
		{
			GameConnection* gConnections = new GameConnection[gNodes[i].numConnections]; 
			for(unsigned int j = 0; j < gNodes[i].numConnections; j++)
			{
				cout << "Current connection:" << i << "----" << endl;
				unsigned int connectionByteOffset = connectionFileOffsets[i];
				unsigned int index = connectionByteOffset + j * 8;
				gConnections[j].cost = *reinterpret_cast<float*>(buf + index);
				cout << "cost:" << i << endl;
				index += 4;
				unsigned int offset = *reinterpret_cast<unsigned int*>(buf + index);
				GameNode* nodeCheck = reinterpret_cast<GameNode*>(buf+offset);
				for(int k= 0; k < numNodes; k++)
				{
					if(nodeCheck->postion == gNodes[k].postion
						&& nodeCheck->numConnections == gNodes[k].numConnections)
					{
						nodeCheck = &gNodes[k];
						break;
					}
				}
				gConnections[j].node = nodeCheck;
				cout << "connection:" << gConnections[j].node << endl;
			}
			gNodes[i].connections = gConnections;
		}
	}
	level->numNodes = numNodes;
	level->nodes = gNodes;
	return level;


}