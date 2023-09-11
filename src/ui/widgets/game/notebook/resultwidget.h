#pragma once

#include <QLabel>
#include <QPushButton>

#include "../../scalablelabel.h"
#include "../../scalablewidget.h"
#include "../../svgpushbutton.h"
#include "../../../../core/engine.h"

/**
 * @brief      This class describes the notebook's result widget.
 */
class ResultWidget : public ScalableWidget
{
    Q_OBJECT

    public:
        /**
         * @brief      Constructs a new instance.
         *
         * @param[in]  action  The action
         * @param[in]  result  The result
         * @param      parent  The parent
         */
        explicit ResultWidget(const QString& action, const QString& result, QWidget *parent = nullptr);

        /**
         * @brief      Destroys the object.
         */
        ~ResultWidget();

        /**
         * @brief      Sets the result to be displayed on the widget.
         *
         * @param[in]  action  The action
         * @param[in]  result  The result
         */
        void setResult(const QString& action, const QString& result);

    signals:
        /**
         * @brief      Called when the user has acknowledged the result.
         */
        void close();

    private:
        /**
         * @brief      Sets up the UI.
         */
        void setupUi();

        QString action;
        QString result;

        // Ui elements
        ScalableLabel* actionLabel;
        QLabel* resultLabel;

        SVGPushButton* closeButton;

        QPixmap background;
};
