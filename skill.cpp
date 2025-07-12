#include "skill.h"

Skill::Skill() : _name("invalid") {}

Skill::Skill(QString name) : _name(name) {
    _iconPath = ":/icons/icons/" + name + "_icon.png";
}

void Skill::levelUp() {
    while (_levelBreakpoint < _currentXp) {
        _currentXp -= _levelBreakpoint;
        _level += 1;
        _levelBreakpoint = _levelBreakpoint * 1.3;
    }
}

void Skill::addXp(int xp) {
    _currentXp += xp;
}
