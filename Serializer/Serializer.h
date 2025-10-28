#pragma once
#include <iostream>
#include <fstream>

class Serializer
{
public:
	template<typename T>
	static void WriteBinaryFileData(std::ofstream& out, const T& val)
	{
		out.write(reinterpret_cast<const char*>(&val), sizeof(T));
	}

	template<typename T>
	static void ReadBinaryFileData(std::ifstream& in, T& val)
	{
		in.read(reinterpret_cast<char*>(&val), sizeof(T));
	}

	static std::string PathToName(std::string path);

	static void Test();

};

