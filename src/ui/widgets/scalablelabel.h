#pragma once

#include <QLabel>

/**
 * @brief      This class describes a QLabel that scales its font.
 */
class ScalableLabel : public QLabel
{
    Q_OBJECT

    public:
        /**
         * @brief      Constructs a new instance.
         *
         * @param[in]  text    The text
         * @param      parent  The parent
         */
        explicit ScalableLabel(const QString& text, QWidget *parent = nullptr, bool useAlternate = false);

        /**
         * @brief      Destroys the object.
         */
        ~ScalableLabel();

    private:
        /**
         * @brief      Paint event handler. See QWidget paint.
         *
         * @param      event  The event
         */
        void paintEvent(QPaintEvent* event) override;

        /**
        * @brief      Resize event handler. See QWidget resize.
        *
        * @param      event  The event
        */
        void resizeEvent(QResizeEvent* event) override;

        bool useAlternate;
};
