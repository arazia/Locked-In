#include "statstab.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QProgressBar>

StatsTab::StatsTab() {
    layout = new QVBoxLayout(this);
    setLayout(layout);
}

QString StatsTab::currentSkill() const {
    return selectedSkill;
}

void StatsTab::loadSetup(const QMap<QString, Skill>& skills) {
    if (layout) {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        skillButtons.clear();
    }

    for (auto it = skills.begin(); it != skills.end(); ++it) {
        const QString& name = it.key();
        const Skill& skill = it.value();

        // QLabel* nameLabel = new QLabel(name);
        // nameLabel->setAlignment(Qt::AlignCenter);
        // QFont font = nameLabel->font();
        // font.setPointSize(14);
        // font.setBold(true);
        // nameLabel->setFont(font);

        QPushButton* nameButton = new QPushButton(name);
        nameButton->setCheckable(true);
        nameButton->setStyleSheet("padding: 6px; font-weight: bold;");
        connect(nameButton, &QPushButton::clicked, this, [this, name]() {
            selectSkill(name);
        });
        skillButtons[name] = nameButton;

        QLabel* levelLabel = new QLabel(QString("Level %1").arg(skill.getLevel()));
        levelLabel->setAlignment(Qt::AlignCenter);
        QFont lvlFont = levelLabel->font();
        lvlFont.setItalic(true);
        levelLabel->setFont(lvlFont);


        // TODO fix later
        QLabel* iconLabel = new QLabel;
        iconLabel->setPixmap(QPixmap(skill._iconPath).scaled(64, 64, Qt::KeepAspectRatio));
        iconLabel->setAlignment(Qt::AlignCenter);

        QProgressBar* xpBar = new QProgressBar;
        xpBar->setMinimum(0);
        xpBar->setMaximum(skill.getBreakpoint());
        xpBar->setValue(skill.getCurrent());
        xpBar->setFormat(QString("%1 / %2 XP").arg(skill.getCurrent()).arg(skill.getBreakpoint()));

        // Add to layout
        this->layout->addWidget(nameButton);
        this->layout->addWidget(levelLabel);
        this->layout->addWidget(iconLabel);
        this->layout->addWidget(xpBar);
    }

    updateButtonStyles();

}

void StatsTab::selectSkill(const QString& skillName) {
    if (skillButtons.contains(skillName)) {
        selectedSkill = skillName;
        updateButtonStyles();
        emit skillSelected(skillName);
    }
}

void StatsTab::updateButtonStyles() {
    for (auto it = skillButtons.begin(); it != skillButtons.end(); ++it) {
        bool isSelected = (it.key() == selectedSkill);
        it.value()->setChecked(isSelected);
        it.value()->setStyleSheet(isSelected ? "background-color: #aaffaa; font-weight: bold;" : "background-color: none; font-weight: bold;");
    }
}
