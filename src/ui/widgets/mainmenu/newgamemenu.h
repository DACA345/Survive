#pragma once
#include <QGridLayout>
#include <QPushButton>

#include "../scalablewidget.h"

class NewGameMenu : public ScalableWidget
{
    Q_OBJECT

    public:
        NewGameMenu(QWidget *parent = nullptr);
        ~NewGameMenu();

    signals:
        void newGameMenuClosed();

    private slots:
        void onNewGameMenuClosed();

    private:
        void displayLevels();
        void setupUi();

        const int columns = 2;

        QList<QString> levels;
        QList<QPushButton*> levelButtons;
        QWidget* levelsWidget;
        QGridLayout* levelsLayout;

        QPushButton* backButton;
};