#pragma once
#include <QGridLayout>
#include <QPushButton>

#include "../scalablewidget.h"

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
        LoadGameMenu(QWidget *parent = nullptr);

        /**
         * @brief      Destroys the object.
         */
        ~LoadGameMenu();

    signals:
        /**
         * @brief      Emitted when the load game menu is closed.
         */
        void loadGameMenuClosed();

    private slots:
        /**
         * @brief      Called when load game menu closed.
         */
        void onLoadGameMenuClosed();

    private:
        /**
         * @brief      Display a user's saves.
         */
        void displaySaves();

        /**
         * @brief      Sets up the UI.
         */
        void setupUi();

        const int columns = 2;

        QList<QString> saves;
        QList<QPushButton*> saveButtons;
        QWidget* savesWidget;
        QGridLayout* savesLayout;

        QPushButton* backButton;
};