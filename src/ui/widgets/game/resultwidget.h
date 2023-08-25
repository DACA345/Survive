#pragma once

#include <QLabel>
#include <QPushButton>

#include "../scalablewidget.h"
#include "../../../core/engine.h"

class ResultWidget : public ScalableWidget
{
    Q_OBJECT

    public:
        explicit ResultWidget(QWidget *parent = nullptr);
        ~ResultWidget();

        void showResult(ActionResult result);

    private:
        void paintEvent(QPaintEvent* event) override;

        void loadGraphics();
        void setupUi();

        // Ui elements
        QLabel* resultLabel;

        QPushButton* closeButton;

        QPixmap background;
};
