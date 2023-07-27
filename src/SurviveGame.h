#pragma once
#include <QMainWindow>

#include "UI/MainMenu.h"

class SurviveGame : public QMainWindow
{
    Q_OBJECT

    public:
        explicit SurviveGame(QWidget* parent = nullptr);
        ~SurviveGame();

    private:
        void resizeEvent(QResizeEvent* event) override;
        void setupUi();
        
        MainMenu* mainMenu = nullptr;
        bool windowSizeInitialized = false;
};