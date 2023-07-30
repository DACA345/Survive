#pragma once
#include <QMainWindow>

#include "ui/mainmenu.h"

class SurviveGame : public QMainWindow
{
    Q_OBJECT

    public:
        explicit SurviveGame(QWidget* parent = nullptr);
        ~SurviveGame();

    private:
        void resizeEvent(QResizeEvent* event) override;

        void setupUiSettings();
        void setupUi();
        
        MainMenu* mainMenu = nullptr;
        bool windowSizeInitialized = false;
};