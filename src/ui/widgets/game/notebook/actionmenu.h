#pragma once

#include "../../scalablewidget.h"
#include "../../svgpushbutton.h"

/**
 * @brief      This class describes the action menu within the notebook.
 */
class ActionMenu : public ScalableWidget
{
    Q_OBJECT

    public:
        /**
         * @brief      Constructs a new instance.
         *
         * @param      parent  The parent
         */
        explicit ActionMenu(QWidget *parent = nullptr);

        /**
         * @brief      Destroys the object.
         */
        ~ActionMenu();

    signals:
        /**
         * @brief      Signal that the user has opted to find food.
         */
        void findFood();

        /**
         * @brief      Signal that the user has opted to find water.
         */
        void findWater();

        /**
         * @brief      Signal that the user has opted to explore.
         */
        void explore();

        /**
         * @brief      Signal that the user has opted to rest.
         */
        void rest();

    private:
        /**
         * @brief      Sets up the UI.
         */
        void setupUi();

        SVGPushButton* findFoodButton;
        SVGPushButton* findWaterButton;
        SVGPushButton* exploreButton;
        SVGPushButton* restButton;
};
