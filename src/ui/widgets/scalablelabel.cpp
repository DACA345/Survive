#include <QFontMetricsF>

#include "scalablelabel.h"

#define START_SIZE 6

ScalableLabel::ScalableLabel(const QString& text, QWidget *parent)
    : QLabel(text, parent)
{

}

void ScalableLabel::paintEvent(QPaintEvent* event)
{
    if (this->text().isEmpty())
    {
        return;
    }

    QFont font = this->font();
    QFontMetricsF fm = QFontMetrics(font);
    QRectF thisRect = QRectF(0, 0, this->width(), this->height());
    QRectF rect = fm.boundingRect(this->text());

    // Find the maximum font size that will fit
    int size = START_SIZE;
    while (rect.width() < thisRect.width() && rect.height() < thisRect.height())
    {
        size++;
        font.setPointSize(size);
        fm = QFontMetrics(font);
        rect = fm.boundingRect(this->text());
    }

    setStyleSheet("font-size: " + QString::number(size - 1) + "px;");

    QLabel::paintEvent(event);
}

ScalableLabel::~ScalableLabel()
{
}
