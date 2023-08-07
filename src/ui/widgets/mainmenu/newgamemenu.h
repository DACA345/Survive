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
        // NOTE(Callum): May need to be its own widget
        struct LevelInfo
        {
            LevelInfo(const QString& path);

            QString name;
            // TODO(Callum): Add background pixmap
        };

        void displayLevels();
        void setupUi();

        const int columns = 2;

        QList<LevelInfo> levels;
        QList<QPushButton*> levelButtons;
        QWidget* levelsWidget;
        QGridLayout* levelsLayout;

        QPushButton* backButton;
};