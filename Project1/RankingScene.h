#pragma once
#include <vector>
#include "FileManager.h"

class Ranking
{
	std::vector<RankingInfo> rankingList;

public:
	Ranking();
	~Ranking();


private:

};


Ranking::Ranking()
{
	rankingList = FileManager::LoadRanking();
}

Ranking::~Ranking()
{


}