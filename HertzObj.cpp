//#include "HertzObj.h"
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <sstream>
//
////Data HertzObj::readOBJ(const char* filePath)
////{
////	Data data;
////	std::ifstream file(filePath);
////	std::string line;
////
////	if (!file.is_open())
////	{
////		std::cout << "ERROR OPENING FILE" << std::endl;
////	}
////
////	while (std::getline(file, line))
////	{
////		std::istringstream iss(line);
////		std::string prefix;
////		iss >> prefix;
////
////		if (prefix == "v")
////		{
////			Vertex vPos;
////			iss >> vPos.x >> vPos.y >> vPos.z;
////			data.verticies.push_back(vPos);
////		}
////
////		else if (prefix == "vn")
////		{
////			Vertex vNormals;
////			iss >> vNormals.x >> vNormals.y >> vNormals.z;
////			data.verticies.push_back(vNormals);
////
////		}
////		else if (prefix == "vt")
////		{
////			Vertex vTexCoords;
////			iss >> vTexCoords.x >> vTexCoords.y >> vTexCoords.z;
////			data.verticies.push_back(vTexCoords);
////		}
////		else if (prefix == "f")
////		{
////			unsigned int vIndex[3], tIndex[3], nIndex[3];
////			char slash;
////			for (int i = 0; i < 3; ++i)
////			{
////				iss >> vIndex[i] >> slash >> tIndex[i] >> slash >> nIndex[i];
////				data.indices.push_back(vIndex[i] - 1);
////			}
////		}
////
////	}
////	file.close();
////	return data;
////
////
//
//}
