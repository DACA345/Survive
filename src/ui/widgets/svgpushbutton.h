#pragma once
#include <QEnterEvent>
#include <QGraphicsOpacityEffect>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSvgRenderer>

/**
 * @brief      This class describes a push button displayed as an SVG.
 */
class SVGPushButton : public QPushButton
{
    Q_OBJECT

    public:
        /**
         * @brief      Creates a new SVG push button.
         *
         * @param[in]  path    The path
         * @param      parent  The parent
         */
        SVGPushButton(const QString& path, QWidget *parent = nullptr);

        /**
         * @brief      Destroys the object.
         */
        ~SVGPushButton();

    private:
        /**
         * @brief      Paint event handler. See QWidget paint.
         *
         * @param      event  The event
         */
        void paintEvent(QPaintEvent* event) override;

        /**
         * @brief      When the mouse enters the widget event handler.
         *
         * @param      event  The event
         */
        void enterEvent(QEnterEvent* event) override;

        /**
         * @brief      When the mouse leaves the widget event handler.
         *
         * @param      event  The event
         */
        void leaveEvent(QEvent* event) override;

        const int duration = 200;
        const double startOpacity = 1.0;
        const double endOpacity = 0.7;

        QSvgRenderer* renderer;

        QParallelAnimationGroup* animationGroup;
        QPropertyAnimation* opacityAnimation;
        QGraphicsOpacityEffect* opacityEffect;
};
