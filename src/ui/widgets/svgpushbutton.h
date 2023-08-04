#pragma once
#include <QEnterEvent>
#include <QGraphicsOpacityEffect>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSvgRenderer>

class SVGPushButton : public QPushButton
{
    Q_OBJECT

    public:
        SVGPushButton(const QString& path, QWidget *parent = nullptr);
        ~SVGPushButton();

    private:
        void paintEvent(QPaintEvent* event) override;

        void enterEvent(QEnterEvent* event);
        void leaveEvent(QEvent* event);

        const int duration = 200;
        const double startOpacity = 1.0;
        const double endOpacity = 0.7;

        QSvgRenderer* renderer;

        QParallelAnimationGroup* animationGroup;
        QPropertyAnimation* opacityAnimation;
        QGraphicsOpacityEffect* opacityEffect;
};
