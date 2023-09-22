#include <QPainter>

#include "pausemenu.h"
#include "../../../config/files.h"

PauseMenu::PauseMenu(QWidget *parent)
    : ScalableWidget(parent)
{
    loadGraphics();
    setupUi();
}

void PauseMenu::paintEvent(QPaintEvent *event)
{
    ScalableWidget::paintEvent(event);
    QPainter painter(this);

    painter.drawPixmap(rect(), overlay.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void PauseMenu::loadGraphics()
{
    overlay = QPixmap(TEXTURE_FILE("ui/pause/background/overlay.svg"));
}

void PauseMenu::setupUi()
{
    // TODO(Callum & Adam): Change to save and exit textures
    saveButton = new SVGPushButton(TEXTURE_FILE("ui/pause/text/save.svg"), this);
    exitButton = new SVGPushButton(TEXTURE_FILE("ui/pause/text/exit.svg"), this);

    backButton = new SVGPushButton(TEXTURE_FILE("mainmenu/icons/return.svg"), this);

    connect(saveButton, &QPushButton::clicked, this, &PauseMenu::save);
    connect(exitButton, &QPushButton::clicked, this, &PauseMenu::exit);
    connect(backButton, &QPushButton::clicked, this, &PauseMenu::resume);

    addWidget(saveButton, 0.3975, 0.4675, 0.205, 0.065);
    addWidget(exitButton, 0.38125, 0.55, 0.2375, 0.065);
    addWidget(backButton, 0.05, 0.025, 0.065, 0.09);
}

PauseMenu::~PauseMenu()
{
}
