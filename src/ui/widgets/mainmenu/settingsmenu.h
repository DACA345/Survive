#pragma once
#include <QSettings>
#include <QComboBox>
#include <QPushButton>
#include <QSvgWidget>

#include "../scalablewidget.h"
#include "../svgpushbutton.h"

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
        explicit SettingsMenu(QWidget* parent = nullptr);

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

    private:
        /**
         * @brief      Paint event handler. See QWidget paint.
         *
         * @param      event  The event
         */
        void paintEvent(QPaintEvent* event) override;

        /**
        * @brief      Loads the stylesheet.
        */
        void loadStylesheet();

        /**
        * @brief      Loads the graphics.
        */
        void loadGraphics();

        /**
         * @brief      Sets up the UI.
         */
        void setupUi();

        QSettings* settings;

        QSvgWidget* title;
        QSvgWidget* resolutionLabel;

        QComboBox* resolutionOption;
        QComboBox* frameOption;

        SVGPushButton* backButton;

        QPixmap background;
        QPixmap overlay1;
};