#pragma once

#include "../../scalablewidget.h"
#include "../../scalablelabel.h"
#include "../../svgpushbutton.h"

/**
 * @brief      This class describes the notebook's sleep widget.
 */
class SleepWidget : public ScalableWidget
{
    Q_OBJECT

    public:
        /**
         * @brief      Constructs a new instance.
         *
         * @param      parent  The parent
         */
        explicit SleepWidget(QWidget *parent = nullptr);

        /**
         * @brief      Destroys the object.
         */
        ~SleepWidget();

    signals:
        /**
         * @brief      Called when the user has opted to sleep.
         */
        void close();

    private:
        /**
         * @brief      Sets up the UI.
         */
        void setupUi();

        ScalableLabel* sleepLabel;
        SVGPushButton* sleepButton;
};
