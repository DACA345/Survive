#pragma once
#include <QPushButton>
#include <QSvgRenderer>

class SVGPushButton : public QPushButton
{
    Q_OBJECT

    public:
        SVGPushButton(const QString& path, QWidget *parent = nullptr);
        ~SVGPushButton();

    private:
        void paintEvent(QPaintEvent* event) override;

        QSvgRenderer* renderer;
        QRect viewBox;
};
