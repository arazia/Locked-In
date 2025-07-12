#include "gamestate.h"

#include <QStandardPaths>
#include <QDir>
#include <QJsonObject>

GameState::GameState() {
    if (!loadFromDisk()) {
        QStringList skills = {
            "Woodcutting", "Fishing", "Mining", "Firemaking"
        };

        for (const QString& s : skills) {
            _skills[s] = Skill(s);
        }
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

        s.levelUp();

        _lockedInActive = false;
    }

    saveToDisk();
}

QString GameState::saveFilePath() const {
    QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/locked_in";
    QDir().mkpath(path);
    return path + "/gamestate.json";
}


void GameState::saveToDisk() {
    QJsonObject root;
    root["activeSkill"] = _activeSkill;
    QJsonObject skillsObj;
    for (auto it = _skills.begin(); it != _skills.end(); ++it) {
        QJsonObject skillJson;
        skillJson["xp"] = it->getCurrent();
        skillJson["xpBreakpoint"] = it->getBreakpoint();
        skillJson["level"] = it->getLevel();
        //skillJson["iconPath"] = it->_iconPath;
        skillsObj[it.key()] = skillJson;
    }
    root["skills"] = skillsObj;

    QFile file(saveFilePath());
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(root).toJson());
        file.close();
    }
}

bool GameState::loadFromDisk() {
    QFile file(saveFilePath());
    if (!file.open(QIODevice::ReadOnly)) return false;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject root = doc.object();
    _activeSkill = root["activeSkill"].toString();
    QJsonObject skillsObj = root["skills"].toObject();
    for (const QString& key : skillsObj.keys()) {
        QJsonObject skillJson = skillsObj[key].toObject();
        Skill skill = Skill(key, skillJson["xp"].toInt(), skillJson["xpBreakpoint"].toInt(), skillJson["level"].toInt());
        //skill.iconPath = skillJson["iconPath"].toString();
        _skills[key] = skill;
    }
    file.close();

    return true;
}













