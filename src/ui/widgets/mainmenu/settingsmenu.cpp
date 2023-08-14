#include <QApplication>
#include <QPainter>
#include <QScreen>

#include "settingsmenu.h"
#include "../../../config/files.h"
#include "../../../config/settings.h"
#include "../../../util/resolution.h"

SettingsMenu::SettingsMenu(QWidget* parent)
    : ScalableWidget(parent)
{
    resize(parent->size());
    settings = new QSettings();

    loadGraphics();
    setupUi();
}

void SettingsMenu::paintEvent(QPaintEvent* event)
{
    ScalableWidget::paintEvent(event);

    QPainter painter(this);

    painter.drawPixmap(rect(), background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    painter.drawPixmap(rect(), overlay1.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void SettingsMenu::loadGraphics()
{
    background = QPixmap(TEXTURE_FILE("mainmenu/settings/background/image.png"));
    overlay1 = QPixmap(TEXTURE_FILE("mainmenu/settings/background/overlay1.svg"));
}

void SettingsMenu::setupUi()
{
    // Labels
    title = new QSvgWidget(TEXTURE_FILE("mainmenu/settings/text/title.svg"), this);
    resolutionLabel = new QSvgWidget(TEXTURE_FILE("mainmenu/settings/text/resolution.svg"), this);

    // Setup resolution and frame options
    QSize maxResolution = QApplication::primaryScreen()->size();
    QList<QSize> resolutionOptions = Resolution::generateResolutions(maxResolution.width(), maxResolution.height());
    resolutionOption = new QComboBox(this);

    for (const QSize& resolution : resolutionOptions)
    {
        resolutionOption->addItem(QString::number(resolution.width()) + "x" + QString::number(resolution.height()), QVariant::fromValue(resolution));
    }

    resolutionOption->setCurrentIndex(
        resolutionOption->findData(
            QVariant::fromValue(
                QSize(settings->value("gui/resolution").value<QSize>()
                )
            )
        )
    );

    frameOption = new QComboBox(this);
    frameOption->addItem("Windowed", QVariant::fromValue(UI_SETTINGS_FRAME_NORMAL));
    frameOption->addItem("Borderless", QVariant::fromValue(UI_SETTINGS_FRAME_FRAMELESS));
    frameOption->addItem("Fullscreen", QVariant::fromValue(UI_SETTINGS_FRAME_FULLSCREEN));
    frameOption->setCurrentIndex(
        frameOption->findData(
            QVariant::fromValue(
                settings->value("gui/frame", UI_SETTINGS_FRAME_NORMAL).value<int>()
            )
        )
    );

    backButton = new SVGPushButton(TEXTURE_FILE("mainmenu/settings/text/back.svg"), this);

    // Setup connections
    connect(resolutionOption, &QComboBox::currentIndexChanged, this, &SettingsMenu::onResolutionOptionChanged);
    connect(frameOption, &QComboBox::currentIndexChanged, this, &SettingsMenu::onFrameOptionChanged);
    connect(backButton, &QPushButton::clicked, this, &SettingsMenu::onSettingsMenuClosed);

    // Add widgets
    addWidget(title, 0.4, 0.0, 0.2, 0.1);
    addWidget(resolutionLabel, 0.4, 0.2, 0.2, 0.1);
    addWidget(resolutionOption, 0.4, 0.3, 0.2, 0.1);
    addWidget(frameOption, 0.4, 0.4, 0.2, 0.1);
    addWidget(backButton, 0.4, 0.85, 0.2, 0.1);
}

void SettingsMenu::onResolutionOptionChanged()
{
    QSize resolution = resolutionOption->currentData().value<QSize>();
    settings->setValue("gui/resolution", resolution);
    emit resolutionOptionChanged(resolution);
}

void SettingsMenu::onFrameOptionChanged()
{
    int frame = frameOption->currentData().value<int>();
    settings->setValue("gui/frame", frame);
    emit frameOptionChanged(frame);
}

void SettingsMenu::onSettingsMenuClosed()
{
    emit settingsMenuClosed();
}

SettingsMenu::~SettingsMenu()
{
    delete settings;

    delete title;
    delete resolutionLabel;
    delete resolutionOption;
    delete frameOption;
}