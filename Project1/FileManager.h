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
		return "saveFile.bin";
	}

public:
	static std::vector<RankingInfo> LoadRanking() 
	{
		std::vector<RankingInfo> ranking;
		std::ifstream file(GetSaveFileName(), std::ios::binary);
		if (file.is_open()) {
			while (file) {
				size_t nameLen;
				if (!file.read(reinterpret_cast<char*>(&nameLen), sizeof(size_t))) break;
				std::string name(nameLen, '\0');
				file.read(&name[0], nameLen);
				unsigned int score;
				file.read(reinterpret_cast<char*>(&score), sizeof(unsigned int));
				ranking.push_back({name, score});
			}
			file.close();
		}

		return ranking;
	}

	static void SaveScore(RankingInfo Info) 
	{
		std::vector<RankingInfo> currentRanking = LoadRanking();
		currentRanking.push_back(Info);

		// Bubble sort
		for (size_t i = 0; i < currentRanking.size() - 1; ++i) {
			for (size_t j = 0; j < currentRanking.size() - i - 1; ++j) {
				if (currentRanking[j].score < currentRanking[j + 1].score) {
					std::swap(currentRanking[j], currentRanking[j + 1]);
				}
			}
		}

		if (currentRanking.size() > 5) {
			currentRanking.resize(5);
		}

		std::ofstream file(GetSaveFileName(), std::ios::binary);
		if (file.is_open()) {
			for (const auto& entry : currentRanking) {
				size_t nameLen = entry.name.size();
				file.write(reinterpret_cast<const char*>(&nameLen), sizeof(size_t));
				file.write(entry.name.c_str(), nameLen);
				file.write(reinterpret_cast<const char*>(&entry.score), sizeof(unsigned int));
			}
			file.close();
		}
	}
};
