#pragma once

#include <QLabel>

class ScalableLabel : public QLabel
{
    Q_OBJECT

    public:
        ScalableLabel(const QString& text, QWidget *parent = nullptr);
        ~ScalableLabel();

    private:
        void paintEvent(QPaintEvent* event) override;
};
