#pragma once
#include <QSettings>
#include <QComboBox>
#include <QPushButton>

#include "../scalablewidget.h"

class SettingsMenu : public ScalableWidget
{
    Q_OBJECT

    public:
        SettingsMenu(QWidget* parent = nullptr);
        ~SettingsMenu();

    signals:
            void resolutionOptionChanged(QSize resolution);
            void frameOptionChanged(int frame);
            void settingsMenuClosed();

    private slots:
        void onResolutionOptionChanged();
        void onFrameOptionChanged();
        void onSettingsMenuClosed();

    private:
        void setupUi();

        QSettings* settings;

        QComboBox* resolutionOption;
        QComboBox* frameOption;

        QPushButton* backButton;
};