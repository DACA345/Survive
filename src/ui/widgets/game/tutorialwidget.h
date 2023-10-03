#pragma once

#include <QSvgWidget>

#include "../scalablelabel.h"
#include "../scalablewidget.h"
#include "../svgpushbutton.h"

#define TUTORIAL_HEADER "Welcome to Survive!"

#define TUTORIAL_BODY \
    "You have found yourself stranded in the remote wilderness with nothing but your notebook and your own survival instincts to see you through.\n" \
    "You need to survive as long as possible making sure that your health(green), thirst(blue), hunger(orange), and energy(yellow) bars don't reach zero.\n" \
    "Each day you'll be given a choice of the following four key options to test your survival ability but be careful you can only perform five actions per day before you tire out and need to rest for the night.\n" \
    "\n" \
    "- Find Food : Attempt to find food in the wilderness. Be warned, not everything is edible.\n" \
    "- Find Water : Attempt to find water. Be wary, not everything is drinkable.\n" \
    "- Explore : Search the wilderness and see what you can find. This could be good for your morale.\n" \
    "- Rest : Stay at camp a while and regain your energy. Ensure you aren't hungry or you might starve.\n" \
    "\n" \
    "Your notebook will help you keep track of your actions taken per day and warn you of any dangerous events in the region.\n" \
    "In the top right of the notebook, you'll be able to view the history of all your days.\n" \
    "\n" \
    "If you need to take a break, click the cog in the top left of your screen and save the game. You'll be able to return to this spot later on when you continue."



class TutorialWidget : public ScalableWidget
{
    Q_OBJECT

public:
    TutorialWidget(QWidget *parent = nullptr);
    ~TutorialWidget();

signals:
    void close();

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
    
    QSvgWidget* bannerWidget;
    ScalableLabel* bodyLabel;

    SVGPushButton* closeButton;

    QPixmap overlay;
};
