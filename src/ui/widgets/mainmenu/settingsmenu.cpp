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

    loadStylesheet();
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

void SettingsMenu::loadStylesheet()
{
    QFile file(TEXTURE_FILE("mainmenu/settings/style/style.qss"));
    file.open(QFile::ReadOnly);
    setStyleSheet(file.readAll());
    file.close();
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

    backButton = new SVGPushButton(TEXTURE_FILE("mainmenu/icons/return.svg"), this);

    // Setup connections
    connect(resolutionOption, &QComboBox::currentIndexChanged, this, &SettingsMenu::onResolutionOptionChanged);
    connect(frameOption, &QComboBox::currentIndexChanged, this, &SettingsMenu::onFrameOptionChanged);
    connect(backButton, &QPushButton::clicked, this, &SettingsMenu::settingsMenuClosed);

    // Add widgets
    addWidget(title, 0.4, 0.075, 0.2, 0.0675);
    addWidget(resolutionLabel, 0.45, 0.25, 0.12, 0.043);
    addWidget(resolutionOption, 0.4, 0.325, 0.2, 0.1);
    addWidget(frameOption, 0.4, 0.435, 0.2, 0.1);
    addWidget(backButton, 0.05, 0.025, 0.065, 0.09);
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

SettingsMenu::~SettingsMenu()
{
    delete settings;

    delete title;
    delete resolutionLabel;
    delete resolutionOption;
    delete frameOption;
}