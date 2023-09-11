#pragma once

#include <QLabel>

#include "actionmenu.h"
#include "historywidget.h"
#include "resultwidget.h"
#include "sleepwidget.h"
#include "../../scalablelabel.h"
#include "../../scalablewidget.h"
#include "../../svgpushbutton.h"

/**
 * @brief      This class describes a notebook widget in the game.
 */
class NotebookWidget : public ScalableWidget
{
    Q_OBJECT

    public:
        /**
         * @brief      Constructs a new instance.
         *
         * @param[in]  engine  The engine
         * @param      parent  The parent
         */
        explicit NotebookWidget(const Engine& engine, QWidget* parent = nullptr);

        /**
         * @brief      Destroys the object.
         */
        ~NotebookWidget();

        /**
         * @brief      Displays the menu for selecting an action.
         *
         * @param[in]  hide  The hide
         */
        void displayActionMenu(bool hide = false);

        /**
         * @brief      Displays the history widget for journal entries.
         *
         * @param[in]  day   The day
         * @param[in]  hide  The hide
         */
        void displayHistoryWidget(int day = -1, bool hide = true);

        /**
         * @brief      Display the results to a user.
         *
         * @param[in]  action  The action
         * @param[in]  result  The result
         * @param[in]  hide    The hide
         */
        void displayResultsWidget(QString action, QString result, bool hide = true);

        /**
         * @brief      Display the option for the user to sleep.
         *
         * @param[in]  hide  The hide
         */
        void displaySleepWidget(bool hide = true);

        /**
         * @brief      Updates the day text.
         */
        void updateDay();

    signals:
        /**
         * @brief      Called when the user has opted to find food.
         */
        void findFood();

        /**
         * @brief      Called when the user has opted to find water.
         */
        void findWater();

        /**
         * @brief      Called when the user has opted to explore.
         */
        void explore();

        /**
         * @brief      Called when the user has opted to rest.
         */
        void rest();

        /**
         * @brief      Called when the user has opted to sleep.
         */
        void sleep();

        /**
         * @brief      Called when the user has acknowledged the result widget.
         */
        void resultAcknowledged();

        /**
         * @brief      Called when the user closes the notebook.
         */
        void close();

    private:
        /**
         * @brief      Enum representing the type of widget being displayed.
         */
        enum class WidgetType
        {
            ACTION_MENU,
            HISTORY_WIDGET,
            RESULTS_WIDGET,
            SLEEP_WIDGET
        };

        /**
         * @brief      Information of the notebook widgets.
         */
        struct WidgetInfo
        {
            WidgetType type;

            // History
            int day;

            // Result
            QString action;
            QString result;
        };

        /**
         * @brief      Paint event handler. See QWidget paint.
         *
         * @param      event  The event
         */
        void paintEvent(QPaintEvent* event) override;

        /**
         * @brief      Loads a stylesheet.
         */
        void loadStylesheet();

        /**
         * @brief      Loads the widget's graphics.
         */
        void loadGraphics();

        /**
         * @brief      Sets up the UI.
         */
        void setupUi();

        /**
         * @brief      Raises the buttons to be on top.
         */
        void raiseButtons();

        /**
         * @brief      Displays the previous widget on the stack.
         */
        void displayPrevious();

        /**
         * @brief      Closes the current widget on the stack.
         *
         * @param[in]  hide  Whether to hide or close
         */
        void closeCurrent(bool hide = false);

        /**
         * @brief      Closes the action menu.
         *
         * @param[in]  hide  Whether to hide or close
         */
        void closeActionMenu(bool hide = false);

        /**
         * @brief      Closes the history widget.
         *
         * @param[in]  hide  Whether to hide or close
         */
        void closeHistoryWidget(bool hide = false);

        /**
         * @brief      Closes the results widget.
         *
         * @param[in]  hide  Whether to hide or close
         */
        void closeResultsWidget(bool hide = false);

        /**
         * @brief      Closes the sleep widget.
         *
         * @param[in]  hide  Whether to hide or close
         */
        void closeSleepWidget(bool hide = false);

        /**
         * The game engine.
         */
        const Engine& engine;

        /**
         * Stack of widgets displayed on the notebook.
         */
        QList<WidgetInfo> widgetStack;

        // Ui elements
        ActionMenu* actionMenu = nullptr;
        HistoryWidget* historyWidget;
        ResultWidget* resultWidget;
        SleepWidget* sleepWidget;

        ScalableLabel *titleLabel;

        SVGPushButton* historyButton;
        SVGPushButton* closeButton;

        QPixmap background;
};
