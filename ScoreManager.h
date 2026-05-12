#pragma once  // Ensures this header is only included once per compilation

#include <string>

class ScoreManager {
public:
    int load();
    void save(int score);

private:

    static inline const std::string filePath = "data/highscore.txt";
};