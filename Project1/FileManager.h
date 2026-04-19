#pragma once
#include <string>
#include <vector>

#include <fstream>
#include <algorithm>
#include <iostream>

// Struct con los datos que guardamos de cada partida para el hall of fame
struct RankingInfo
{
	std::string name; // Alias que escriba el jugador
	unsigned int score; // Puntos que hizo

    // Sobrescribo el '<' para poder ordenar el top fácilmente de mejor a peor
	bool operator<(const RankingInfo& other) const {
		return score > other.score; 
	}
};

// Me sirve de gestor de guardado (solo tiene metodos estáticos así que no instancio nada)
class FileManager {

	static std::string GetSaveFileName() {
		return "saveFile.bin"; // Metemos todo al fichero binario
	}

public:
    // Función para recuperar la lista del Top 5
	static std::vector<RankingInfo> LoadRanking() 
	{
		std::vector<RankingInfo> ranking;
		std::ifstream file(GetSaveFileName(), std::ios::binary);
		if (file.is_open()) {
			while (file) {
                // Leo primero cuánto ocupa el nombre y luego pillo los caracteres de golpe
				size_t nameLen;
				if (!file.read(reinterpret_cast<char*>(&nameLen), sizeof(size_t))) break; // Llegamos al final del archivo

				std::string name(nameLen, '\0');
				file.read(&name[0], nameLen);
				
                // Leo los puntitos del tirón
				unsigned int score;
				file.read(reinterpret_cast<char*>(&score), sizeof(unsigned int));
				
                // Y para adentro
				ranking.push_back({name, score});
			}
			file.close();
		}

		return ranking;
	}

    // Guarda el nuevo record de esta partida (si entra en el top 5 claro)
	static void SaveScore(RankingInfo Info) 
	{
		std::vector<RankingInfo> currentRanking = LoadRanking(); // Cargo los que ya estaban
		currentRanking.push_back(Info); // Meto el nuevo notas

		// Ordenación por burbuja, un clásico de programación jajaja (el que más puntos tiene va el primero)
		for (size_t i = 0; i < currentRanking.size() - 1; ++i) {
			for (size_t j = 0; j < currentRanking.size() - i - 1; ++j) {
				if (currentRanking[j].score < currentRanking[j + 1].score) {
					std::swap(currentRanking[j], currentRanking[j + 1]);
				}
			}
		}

		// Si me he pasado de 5 récords cortamos la lista (que se fastidie el peor de ellos)
		if (currentRanking.size() > 5) {
			currentRanking.resize(5);
		}

		// Reescribo el archivo enterito con la nueva lista actualizada por si acaso
		std::ofstream file(GetSaveFileName(), std::ios::binary);
		if (file.is_open()) {
			for (const auto& entry : currentRanking) {
				size_t nameLen = entry.name.size();
				file.write(reinterpret_cast<const char*>(&nameLen), sizeof(size_t));
				file.write(entry.name.c_str(), nameLen);
				file.write(reinterpret_cast<const char*>(&entry.score), sizeof(unsigned int));
			}
			file.close(); // Y lo cierro, muy importante
		}
	}
};
