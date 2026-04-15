#pragma once
#include <string>
#include <vector>

struct RankingInfo
{
	std::string name;
	unsigned int score;
};



class FileManager {

	const std::string saveFile = "saveFile.bin";



public:
	static void SaveScore(RankingInfo Info) 
	{


	}

	static std::vector<RankingInfo> LoadRanking() 
	{

	}
};
