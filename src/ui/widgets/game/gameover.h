#pragma once

#include <QPixmap>

#include "../scalablewidget.h"
#include "../svgpushbutton.h"

class GameOver : public ScalableWidget
{
    Q_OBJECT

    public:
        GameOver(QWidget *parent = nullptr);
        ~GameOver();

    signals:
        void close();

    private:
        void paintEvent(QPaintEvent* event) override;

        void loadGraphics();
        void setupUi();

        QPixmap background;

        SVGPushButton* closeButton;
};
