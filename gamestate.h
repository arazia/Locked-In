#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QString>
#include <Skill.h>
#include <QElapsedTimer>
#include <QMap>

class GameState
{
public:
    GameState();

    void lockedIn();
    void lockedOut(int intendedDuration);
    inline void setActive(bool active) {
        _lockedInActive = active;
    }

    inline void setActiveSkill(const QString& skillName) {
        _activeSkill = skillName;
        saveToDisk();
    }

    inline const Skill &getActiveSkill() {
        return _skills[_activeSkill];
    }

    inline const QMap<QString, Skill> &getSkills() {
        return _skills;
    }

    void saveToDisk();
    bool loadFromDisk();

private:
    QMap<QString, Skill> _skills;
    QString _activeSkill;
    bool _lockedInActive = false;
    QElapsedTimer _lockTimer;

    QString saveFilePath() const;
};

#endif // GAMESTATE_H
