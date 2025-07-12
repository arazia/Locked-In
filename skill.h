#ifndef SKILL_H
#define SKILL_H

#include <QString>

class Skill
{
public:

    Skill();

    Skill(QString name);

    void levelUp();

    void addXp(int xp);

    inline int getBreakpoint() const {
        return _levelBreakpoint;
    }

    inline int getCurrent() const {
        return _currentXp;
    }

    QString _iconPath;
private:
    QString _name;
    int _currentXp = 0;
    int _levelBreakpoint = 100;
    int _level = 1;
};

#endif // SKILL_H
