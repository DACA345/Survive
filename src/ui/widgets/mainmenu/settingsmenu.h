#pragma once
#include <QSettings>
#include <QComboBox>
#include <QPushButton>

#include "../scalablewidget.h"

/**
 * @brief      This class describes a settings menu.
 */
class SettingsMenu : public ScalableWidget
{
    Q_OBJECT

    public:
        /**
         * @brief      Creates a new settings menu.
         *
         * @param      parent  The parent
         */
        SettingsMenu(QWidget* parent = nullptr);

        /**
         * @brief      Destroys the object.
         */
        ~SettingsMenu();

    signals:
        /**
         * @brief      Emitted when the resolution option is changed.
         *
         * @param[in]  resolution  The resolution
         */
        void resolutionOptionChanged(QSize resolution);

        /**
         * @brief      Emitted when the frame option is changed.
         *
         * @param[in]  frame  The frame
         */
        void frameOptionChanged(int frame);

        /**
         * @brief      Emitted when the settings menu is closed.
         */
        void settingsMenuClosed();

    private slots:
        /**
         * @brief      Called when resolution option changed.
         */
        void onResolutionOptionChanged();

        /**
         * @brief      Called when frame option changed.
         */
        void onFrameOptionChanged();

        /**
         * @brief      Called when settings menu closed.
         */
        void onSettingsMenuClosed();

    private:
        /**
         * @brief      Sets up the UI.
         */
        void setupUi();

        QSettings* settings;

        QComboBox* resolutionOption;
        QComboBox* frameOption;

        QPushButton* backButton;
};