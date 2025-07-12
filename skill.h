#ifndef SKILL_H
#define SKILL_H

#include <QString>

class Skill
{
public:

    Skill();

    Skill(QString name);

    inline Skill(QString name, int currentXp, int levelBreakpoint, int level) :
        _name(name), _currentXp(currentXp), _levelBreakpoint(levelBreakpoint), _level(level) {
        _iconPath = ":/icons/icons/" + name + "_icon.png";
    };

    void levelUp();

    void addXp(int xp);

    inline int getBreakpoint() const {
        return _levelBreakpoint;
    }

    inline int getCurrent() const {
        return _currentXp;
    }

    inline int getLevel() const {
        return _level;
    }

    QString _iconPath;
private:
    QString _name;
    int _currentXp = 0;
    int _levelBreakpoint = 100;
    int _level = 1;
};

#endif // SKILL_H
