#include <QFontMetricsF>

#include "scalablelabel.h"

#define START_SIZE 6

ScalableLabel::ScalableLabel(const QString& text, QWidget *parent, bool useAlternate)
    : QLabel(text, parent)
{
    this->useAlternate = useAlternate;
}

void ScalableLabel::paintEvent(QPaintEvent* event)
{
    if (this->text().isEmpty() || useAlternate)
    {
        QLabel::paintEvent(event);
        return;
    }

    QFont font = this->font();
    QFontMetricsF fm = QFontMetrics(font);
    QRectF thisRect = QRectF(0, 0, this->width(), this->height());
    QRectF rect = fm.boundingRect(this->text());

    // Find the maximum font size that will fit
    int size = font.pointSize();
    size = size <= 0 ? START_SIZE : size;
    while (rect.width() < thisRect.width() && rect.height() < thisRect.height())
    {
        size++;
        font.setPointSize(size);
        fm = QFontMetricsF(font);
        rect = fm.boundingRect(this->text());
    }

    setStyleSheet("font-size: " + QString::number(size - 1) + "px;");
    QLabel::paintEvent(event);
}

void ScalableLabel::resizeEvent(QResizeEvent* event)
{
    if (this->text().isEmpty() || !useAlternate)
    {
        QLabel::resizeEvent(event);
        return;
    }

    QString text = this->text();
    QRect rectLbl = contentsRect();
    QFont font = this->font();
    int size = font.pointSize();

    size = size <= 2 ? START_SIZE : size;

    QFontMetrics fontMetrics(font);
    QRect rect = fontMetrics.boundingRect(rectLbl, Qt::TextWordWrap, text);
    int step = rect.height() > rectLbl.height() ? -1 : 1;
    while (true)
    {
        font.setPointSize(size + step);
        QFontMetrics fontMetrics(font);
        rect = fontMetrics.boundingRect(rectLbl, Qt::TextWordWrap, text);
        if (size <= 2)
        {
            break;
        }
        if (step < 0)
        {
            size += step;
            if (rect.height() < rectLbl.height()) break;
        }
        else
        {
            if (rect.height() > rectLbl.height()) break;
            size += step;
        }
    }

    font.setPointSize(size);
    setFont(font);

    QLabel::resizeEvent(event);
}

ScalableLabel::~ScalableLabel()
{
}
