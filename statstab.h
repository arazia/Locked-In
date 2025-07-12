#ifndef STATSTAB_H
#define STATSTAB_H

#include <QWidget>
#include <skill.h>
#include <QPushButton>
#include <QVBoxLayout>

class StatsTab : public QWidget
{
    Q_OBJECT
signals:
    void skillSelected(const QString& skillName);

public:
    StatsTab();
    QString currentSkill() const;
    void loadSetup(const QMap<QString, Skill>& skills);
    void selectSkill(const QString& skillName);
    inline void toggleButtons(bool enabled) {
        for (auto it = skillButtons.begin(); it != skillButtons.end(); ++it) {
            it.value()->setEnabled(enabled);
        }
    }

private:
    void updateButtonStyles();

    QVBoxLayout *layout;
    QString selectedSkill;
    // scary pointer
    QMap<QString, QPushButton*> skillButtons;
};

#endif // STATSTAB_H
