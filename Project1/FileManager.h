#pragma once
#include <string>
#include <vector>

#include <fstream>
#include <algorithm>
#include <iostream>

struct RankingInfo
{
	std::string name;
	unsigned int score;

	bool operator<(const RankingInfo& other) const {
		return score > other.score; 
	}
};

class FileManager {

	static std::string GetSaveFileName() {
		return "saveFile.txt";
	}

public:
	static std::vector<RankingInfo> LoadRanking() 
	{
		std::vector<RankingInfo> ranking;
		std::ifstream file(GetSaveFileName());
		if (file.is_open()) {
			std::string name;
			unsigned int score;
			while (file >> name >> score) {
				ranking.push_back({name, score});
			}
			file.close();
		}
		std::sort(ranking.begin(), ranking.end());
		return ranking;
	}

	static void SaveScore(RankingInfo Info) 
	{
		std::vector<RankingInfo> currentRanking = LoadRanking();
		currentRanking.push_back(Info);
		std::sort(currentRanking.begin(), currentRanking.end());

		if (currentRanking.size() > 5) {
			currentRanking.resize(5);
		}

		std::ofstream file(GetSaveFileName());
		if (file.is_open()) {
			for (int i = 0; i < currentRanking.size(); i++) {
				file << currentRanking[i].name << " " << currentRanking[i].score << "\n";
			}
			file.close();
		}
	}
};
