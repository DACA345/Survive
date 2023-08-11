#pragma once
#include <QMainWindow>

#include "ui/mainmenu.h"
#include "ui/game.h"

class SurviveGame : public QMainWindow
{
    Q_OBJECT

    public:
        explicit SurviveGame(QWidget* parent = nullptr);
        ~SurviveGame();

    private slots:
        void onNewGame(const QString& id);

    private:
        void resizeEvent(QResizeEvent* event) override;

        void setupUiSettings();
        void setupUi();
        
        MainMenu* mainMenu;
        Game* game;

        bool windowSizeInitialized = false;
};