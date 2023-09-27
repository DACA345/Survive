#pragma once
#include <QGridLayout>
#include <QPushButton>

#include "../scalablewidget.h"
#include "../svgpushbutton.h"

// NOTE(Callum): This is currently pretty much the same as NewGameMenu
// Could be refactored to use a base class
// Assuming that the two menu's will diverge in the future

/**
 * @brief      This class describes the load game menu.
 */
class LoadGameMenu : public ScalableWidget
{
    Q_OBJECT

    public:
        /**
         * @brief      Creates a new load game menu instance.
         *
         * @param      parent  The parent
         */
        explicit LoadGameMenu(QWidget *parent = nullptr);

        /**
         * @brief      Destroys the object.
         */
        ~LoadGameMenu();

    signals:
        /**
         * @brief      Emitted when the load game menu is closed.
         */
        void loadGameMenuClosed();

        /**
         * @brief      Emitted when a save is selected.
         *
         * @param[in]  save  The save
         */
        void saveSelected(QString save);

    private:
        /**
         * @brief      Paint event handler. See QWidget paint.
         *
         * @param      event  The event
         */
        void paintEvent(QPaintEvent* event) override;

        /**
         * @brief      Display a user's saves.
         */
        void displaySaves();

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

        const int columns = 2;

        QList<QString> saves;
        QList<QPushButton*> saveButtons;
        QWidget* savesWidget;
        QGridLayout* savesLayout;

        SVGPushButton* backButton;

        QPixmap background;
        QPixmap overlay1;
};