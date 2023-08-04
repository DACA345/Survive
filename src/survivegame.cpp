#include "survivegame.h"
#include "config/settings.h"

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
    // Hide and reshow to cover changes
    hide();

    QSettings settings;

    QSize resSize = settings.value("gui/resolution").value<QSize>();
    if (!resSize.isValid() || resSize.isNull() || resSize.isEmpty())
    {
        QSize resolution = QSize(800, 600);
        setFixedSize(resolution);
        settings.setValue("gui/resolution", resolution);
    }
    else
    {
        setFixedSize(resSize);
    }

    int frame = settings.value("gui/frame").value<int>();
    if (frame == UI_SETTINGS_FRAME_FRAMELESS)
    {
        // Prevent taskbar blocking the app
        setWindowFlag(Qt::WindowStaysOnTopHint);
        setWindowFlag(Qt::FramelessWindowHint);
    }
    else
    {
        setWindowFlag(Qt::WindowStaysOnTopHint, false);
        setWindowFlag(Qt::FramelessWindowHint, false);
        if (frame == UI_SETTINGS_FRAME_FULLSCREEN)
        {
            showFullScreen();
        }
        else
        {
            showNormal();
        }
    }

    show();
}

void SurviveGame::setupUi()
{
    mainMenu = new MainMenu(this);
    setCentralWidget(mainMenu);

    connect(mainMenu, &MainMenu::uiOptionChanged, this, &SurviveGame::setupUiSettings);
}

SurviveGame::~SurviveGame()
{
    delete mainMenu;
}