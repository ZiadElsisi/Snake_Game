#include "ScoreManager.h"
#include <fstream>

// load() Reads the high score from the file.
// Returns 0 on any failure (missing file, bad data, etc.)

int ScoreManager::load() {

    std::ifstream file(filePath);

    if (!file) {
        return 0;
    }

    int highScore = 0;

    if (!(file >> highScore)) {
        return 0;
    }

    return highScore;
}

// save(int score) — Saves the score only if it beats the current best.

void ScoreManager::save(int score) {
    // First, find out what the current high score is.
    int currentBest = load();

    // Only update the file if the new score is strictly better.
    if (score <= currentBest) {
        return;  // Not a new record — do nothing
    }

    // Open the file for writing.
    // std::ofstream creates the file if it doesn't exist.
    // If it does exist, it OVERWRITES the contents entirely.
    std::ofstream file(filePath);

    // Guard against the case where the folder doesn't exist or the system denies write access.
    if (!file) {
        return;  // Fail silently — can't write, just move on
    }

    // Write the new high score as a plain integer.
    file << score;

    // ofstream flushes and closes automatically when it goes out of scope.
}