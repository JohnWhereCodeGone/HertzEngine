#include "Serializer.h"
#include <iostream>
#include <filesystem>

std::string Serializer::PathToName(std::string path)
{
	
	std::filesystem::path temp(path);

	std::string name = temp.stem().string();

	std::cout << "file name is " << name << std::endl;

	return name;

}

void Serializer::Test()
{
	float testData = 4535.f;

	std::ofstream outFile("./Resources/TestData.mesh", std::ios::binary);
	WriteBinaryFileData(outFile, testData);
	outFile.close();

	float loadTestData = 0.f;
	std::ifstream inFile("TestData.mesh", std::ios::binary);
	ReadBinaryFileData(inFile, loadTestData);

	std::cout << "LOADED DATA TEST: " << loadTestData << std::endl;

}
