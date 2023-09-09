#pragma once

#include <QLabel>
#include <QPushButton>

#include "../../scalablelabel.h"
#include "../../scalablewidget.h"
#include "../../svgpushbutton.h"
#include "../../../../core/engine.h"

class ResultWidget : public ScalableWidget
{
    Q_OBJECT

    public:
        explicit ResultWidget(QWidget *parent = nullptr);
        ~ResultWidget();

        void setResult(const QString& action, const QString& result);

    signals:
        void close();

    private:
        void setupUi();

        // Ui elements
        ScalableLabel* actionLabel;
        QLabel* resultLabel;

        SVGPushButton* closeButton;

        QPixmap background;
};
