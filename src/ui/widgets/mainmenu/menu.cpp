#include <QApplication>
#include <QPainter>

#include "menu.h"
#include "../../../config/files.h"

Menu::Menu(QWidget *parent)
    : ScalableWidget(parent)
{
    resize(parent->size());

    loadGraphics();
    setupUi();
}

void Menu::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    painter.drawPixmap(rect(), background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    painter.drawPixmap(rect(), overlay1.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    painter.drawPixmap(rect(), overlay2.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void Menu::loadGraphics()
{
    // Load background
    background = QPixmap(TEXTURE_FILE("mainmenu/menu/background/image.png"));
    overlay1 = QPixmap(TEXTURE_FILE("mainmenu/menu/background/overlay1.svg"));
    overlay2 = QPixmap(TEXTURE_FILE("mainmenu/menu/background/overlay2.svg"));
}

void Menu::setupUi()
{
    // Create game title
    menuTitle = new QSvgWidget(TEXTURE_FILE("mainmenu/menu/text/title.svg"), this);

    // Create buttons for main menu
    newGameButton = new SVGPushButton(TEXTURE_FILE("mainmenu/menu/text/newgame.svg"), this);
    loadGameButton = new SVGPushButton(TEXTURE_FILE("mainmenu/menu/text/loadgame.svg"), this);
    settingsButton = new SVGPushButton(TEXTURE_FILE("mainmenu/menu/text/settings.svg"), this);
    exitButton = new SVGPushButton(TEXTURE_FILE("mainmenu/menu/text/exit.svg"), this);

    // Setup button signals
    connect(newGameButton, &QPushButton::clicked, this, &Menu::onNewGameMenuOpened);
    connect(loadGameButton, &QPushButton::clicked, this, &Menu::onLoadGameMenuOpened);
    connect(settingsButton, &QPushButton::clicked, this, &Menu::onSettingsMenuOpened);
    connect(exitButton, &QPushButton::clicked, this, &QApplication::quit);

    // Setup graphics
    //setupGraphics();

    // Specify the widgets should scale with the window
    //0.135 spacing
    addWidget(menuTitle, 0.02, 0.01, 0.425, 0.14);
    addWidget(newGameButton, 0.055, 0.45, 0.3, 0.075);
    addWidget(loadGameButton, 0.055, 0.585, 0.31, 0.075);
    addWidget(settingsButton, 0.055, 0.72, 0.265, 0.075);
    addWidget(exitButton, 0.055, 0.855, 0.115, 0.075);
}

void Menu::onNewGameMenuOpened()
{
    emit newGameMenuOpened();
}

void Menu::onLoadGameMenuOpened()
{
    emit loadGameMenuOpened();
}

void Menu::onSettingsMenuOpened()
{
    emit settingsMenuOpened();
}

Menu::~Menu()
{
    delete menuTitle;

    delete newGameButton;
    delete loadGameButton;
    delete settingsButton;
    delete exitButton;
}
