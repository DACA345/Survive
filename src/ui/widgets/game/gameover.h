#pragma once

#include <QPixmap>

#include "../scalablewidget.h"
#include "../svgpushbutton.h"

/**
 * @brief      This class describes the game over screen.
 */
class GameOver : public ScalableWidget
{
    Q_OBJECT

    public:
        /**
         * @brief      Constructs a new instance.
         *
         * @param      parent  The parent
         */
        explicit GameOver(QWidget *parent = nullptr);

        /**
         * @brief      Destroys the object.
         */
        ~GameOver();

    signals:
        /**
         * @brief      Called when the user closes the widget.
         */
        void close();

    private:
        /**
         * @brief      Paint event handler. See QWidget paint.
         *
         * @param      event  The event
         */
        void paintEvent(QPaintEvent* event) override;

        /**
         * @brief      Loads the widget's graphics.
         */
        void loadGraphics();

        /**
         * @brief      Sets up the UI.
         */
        void setupUi();

        QPixmap background;

        SVGPushButton* closeButton;
};
