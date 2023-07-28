#include <QApplication>
#include <QScreen>

#include "SurviveGame.h"
#include "Settings.h"

SurviveGame::SurviveGame(QWidget* parent)
    : QMainWindow(parent)
{
    setupUiSettings();
}

void SurviveGame::resizeEvent(QResizeEvent* event)
{
    if (!windowSizeInitialized)
    {
        setupUi();
    }

    windowSizeInitialized = true;
    QMainWindow::resizeEvent(event);
}

void SurviveGame::setupUiSettings()
{
    QSettings settings;

    QSize resSize = settings.value("gui/resolution").value<QSize>();
    if (resSize.isNull())
    {
        QSize resolution = QApplication::primaryScreen()->size();
        setFixedSize(resolution);
        settings.setValue("gui/resolution", resolution);
    }
    else
    {
        setFixedSize(resSize);
    }

    int frame = settings.value("gui/frame").value<int>();
    if (frame == UI_SETTINGS_FRAME_NORMAL)
    {
        
    }
    else if (frame == UI_SETTINGS_FRAME_FRAMELESS)
    {
        // Prevent taskbar blocking the app
        setWindowFlag(Qt::WindowStaysOnTopHint);
        setWindowFlag(Qt::FramelessWindowHint);
    }
    else if (frame == UI_SETTINGS_FRAME_FULLSCREEN)
    {
        showFullScreen();
    }
}

void SurviveGame::setupUi()
{
    mainMenu = new MainMenu(this);
    setCentralWidget(mainMenu);
}

SurviveGame::~SurviveGame()
{
    delete mainMenu;
}