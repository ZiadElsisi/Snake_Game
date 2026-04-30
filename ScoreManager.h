#pragma once  // Ensures this header is only included once per compilation

#include <string>

class ScoreManager {
public:
    // Reads and returns the high score from file.
    // Returns 0 if the file doesn't exist or contains invalid data.
    int load();

    // Saves the score to file only if it's higher than the current high score.
    void save(int score);

private:
    // The path to the high score file.
    // 'const' means it never changes. 'inline' allows definition in the header.
    static inline const std::string filePath = "data/highscore.txt";
};