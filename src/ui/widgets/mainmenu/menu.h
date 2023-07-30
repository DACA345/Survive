#pragma once
#include <QLabel>
#include <QPushButton>

#include "../scalablewidget.h"

class Menu : public ScalableWidget
{
    Q_OBJECT

    public:
        Menu(QWidget *parent = nullptr);
        ~Menu();

    signals:
        void settingsMenuOpened();

    private slots:
        void onSettingsMenuOpened();

    private:
        void setupUi();

        // Ui attributes
        QLabel* menuTitle;

        QPushButton* newGameButton;
        QPushButton* loadGameButton;
        QPushButton* settingsButton;
        QPushButton* exitButton;
};
