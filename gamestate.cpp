#include "gamestate.h"

GameState::GameState() {
    QStringList skills = {
        "Woodcutting", "Fishing", "Mining", "Firemaking"
    };

    for (const QString& s : skills) {
        _skills[s] = Skill(s);
    }
}

/**
 * @brief GameState::lockedIn
 * Precondition: _activeSkill must not be NULL
 */
void GameState::lockedIn() {
    _lockTimer.start();
    _lockedInActive = true;
}

void GameState::lockedOut(int intendedDuration) {
    if (_lockedInActive) {
        int duration = _lockTimer.elapsed() / 1000;

        float multiplier;
        // maximum multiplier at approx. 90 minutes
        if (_lockTimer.elapsed() / 1000 < intendedDuration) {
            multiplier = 0.1;
        } else {
            multiplier = qMin(5.0, 1.0 + intendedDuration / 1800.0);
        }
        int xpGained = qRound(duration * multiplier);

        Skill& s = _skills[_activeSkill];
        s.addXp(xpGained);

        _lockedInActive = false;
    }
}
