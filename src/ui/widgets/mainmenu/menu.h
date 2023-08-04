#pragma once
#include <QPushButton>
#include <QSvgWidget>

#include "../scalablewidget.h"
#include "../svgpushbutton.h"

class Menu : public ScalableWidget
{
    Q_OBJECT

    public:
        Menu(QWidget *parent = nullptr);
        ~Menu();

    signals:
        void newGameMenuOpened();
        void loadGameMenuOpened();
        void settingsMenuOpened();

    private slots:
        void onNewGameMenuOpened();
        void onLoadGameMenuOpened();
        void onSettingsMenuOpened();

    private:
        void paintEvent(QPaintEvent* event) override;

        void loadGraphics();
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
