#pragma once

#include "../scalablewidget.h"
#include "../svgpushbutton.h"

class PauseMenu : public ScalableWidget
{
    Q_OBJECT

    public:
        /**
         * @brief      Constructs a new instance.
         *
         * @param      parent  The parent
         */
        explicit PauseMenu(QWidget *parent = nullptr);

        /**
         * @brief      Destroys the object.
         */
        ~PauseMenu();

    signals:
        /**
         * @brief      Emitted when the user wants to resume.
         */
        void resume();

        /**
         * @brief      Emitted when the user wants to save.
         */
        void save();

        /**
         * @brief      Emitted when the user wants to exit.
         */
        void exit();

    private:
        /**
         * @brief      Paint event handler. See QWidget paint.
         *
         * @param      event  The event
         */
        void paintEvent(QPaintEvent* event) override;

        /**
        * @brief      Loads graphics for the widget.
        */
        void loadGraphics();

        /**
         * @brief      Sets up the UI.
         */
        void setupUi();

        SVGPushButton* saveButton;
        SVGPushButton* exitButton;

        SVGPushButton* backButton;

        QPixmap overlay;
};
