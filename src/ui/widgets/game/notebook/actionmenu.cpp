#include "actionmenu.h"
#include "../../../../config/files.h"

ActionMenu::ActionMenu(QWidget *parent)
    : ScalableWidget(parent)
{
    setupUi();
}

void ActionMenu::setupUi()
{
    findFoodButton = new SVGPushButton(TEXTURE_FILE("ui/notebook/text/food.svg"), this);
    findWaterButton = new SVGPushButton(TEXTURE_FILE("ui/notebook/text/water.svg"), this);
    exploreButton = new SVGPushButton(TEXTURE_FILE("ui/notebook/text/explore.svg"), this);
    restButton = new SVGPushButton(TEXTURE_FILE("ui/notebook/text/rest.svg"), this);

    connect(findFoodButton, &QPushButton::clicked, this, &ActionMenu::findFood);
    connect(findWaterButton, &QPushButton::clicked, this, &ActionMenu::findWater);
    connect(exploreButton, &QPushButton::clicked, this, &ActionMenu::explore);
    connect(restButton, &QPushButton::clicked, this, &ActionMenu::rest);

#define UI_NOTEBOOK_ACTION_X(width) ((1 - width) / 2)
#define UI_NOTEBOOK_ACTION_Y 0.25
#define UI_NOTEBOOK_ACTION_Y_GAP 0.15
#define UI_NOTEBOOK_ACTION_HEIGHT 0.06

    addWidget(findFoodButton, UI_NOTEBOOK_ACTION_X(0.35), UI_NOTEBOOK_ACTION_Y, 0.35, UI_NOTEBOOK_ACTION_HEIGHT);
    addWidget(findWaterButton, UI_NOTEBOOK_ACTION_X(0.42), UI_NOTEBOOK_ACTION_Y + UI_NOTEBOOK_ACTION_Y_GAP, 0.42, UI_NOTEBOOK_ACTION_HEIGHT);
    addWidget(exploreButton, UI_NOTEBOOK_ACTION_X(0.325), UI_NOTEBOOK_ACTION_Y + UI_NOTEBOOK_ACTION_Y_GAP * 2, 0.325, UI_NOTEBOOK_ACTION_HEIGHT);
    addWidget(restButton, UI_NOTEBOOK_ACTION_X(0.185), UI_NOTEBOOK_ACTION_Y + UI_NOTEBOOK_ACTION_Y_GAP * 3, 0.185, UI_NOTEBOOK_ACTION_HEIGHT);
}

ActionMenu::~ActionMenu()
{

}
