#pragma once
#include <QPushButton>
#include <QSvgWidget>

#include "../scalablewidget.h"
#include "../svgpushbutton.h"

/**
 * @brief      This class describes the mainmenu menu.
 */
class Menu : public ScalableWidget
{
    Q_OBJECT

    public:
        /**
         * @brief      Creates a new menu instance.
         *
         * @param      parent  The parent
         */
        explicit Menu(QWidget *parent = nullptr);

        /**
         * @brief      Destroys the object.
         */
        ~Menu();

    signals:
        /**
         * @brief      Emitted when the new game menu is opened.
         */
        void newGameMenuOpened();

        /**
         * @brief      Emitted when the load game menu is opened.
         */
        void loadGameMenuOpened();

        /**
         * @brief      Emitted when the settings menu is opened.
         */
        void settingsMenuOpened();

    private slots:
        /**
         * @brief      Called when new game menu opened.
         */
        void onNewGameMenuOpened();

        /**
         * @brief      Called when load game menu opened.
         */
        void onLoadGameMenuOpened();

        /**
         * @brief      Called when settings menu opened.
         */
        void onSettingsMenuOpened();

    private:
        /**
         * @brief      Paint event handler. See QWidget paint.
         *
         * @param      event  The event
         */
        void paintEvent(QPaintEvent* event) override;

        /**
         * @brief      Loads graphics for the widget.
         */
        void loadGraphics();

        /**
         * @brief      Sets up the UI.
         */
        void setupUi();

        // Ui attributes
        QSvgWidget* menuTitle;

        SVGPushButton* newGameButton;
        SVGPushButton* loadGameButton;
        SVGPushButton* settingsButton;
        SVGPushButton* exitButton;

        QPixmap background;
        QPixmap overlay1;
        QPixmap overlay2;
};
