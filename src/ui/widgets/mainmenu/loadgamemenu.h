#pragma once
#include <QGridLayout>
#include <QPushButton>

#include "../scalablewidget.h"

// NOTE(Callum): This is currently pretty much the same as NewGameMenu
// Could be refactored to use a base class
// Assuming that the two menu's will diverge in the future
class LoadGameMenu : public ScalableWidget
{
    Q_OBJECT;

    public:
        LoadGameMenu(QWidget *parent = nullptr);
        ~LoadGameMenu();

    signals:
        void loadGameMenuClosed();

    private slots:
        void onLoadGameMenuClosed();

    private:
        void displaySaves();
        void setupUi();

        const int columns = 2;

        QList<QString> saves;
        QList<QPushButton*> saveButtons;
        QWidget* savesWidget;
        QGridLayout* savesLayout;

        QPushButton* backButton;
};