#pragma once
#include <QGridLayout>
#include <QPushButton>
#include <QSvgRenderer>

#include "../scalablewidget.h"

/**
 * @brief      This class describes a level information widget.
 */
class LevelInfoWidget : public ScalableWidget
{
    Q_OBJECT

public:
    /**
     * @brief      Creates a new level information widget.
     *
     * @param[in]  levelJson  The level json
     * @param      parent     The parent
     */
    LevelInfoWidget(const QString& levelJson, QWidget* parent = nullptr);

    /**
     * @brief      Destroys the object.
     */
    ~LevelInfoWidget();

signals:
    /**
     * @brief      Emitted when a level is selected.
     *
     * @param[in]  levelName  The level name
     */
    void levelSelected(const QString& levelName);

private:
    /**
     * @brief      Paint event handler. See QWidget paint.
     *
     * @param      event  The event
     */    
    void paintEvent(QPaintEvent* event) override;

    /**
     * @brief      Mouse press event handler. See QWidget mousePressEvent.
     *
     * @param      event  The event
     */
    void mousePressEvent(QMouseEvent* event) override;

    /**
     * @brief      When the mouse enters the widget event handler.
     *
     * @param      event  The event
     */
    void enterEvent(QEnterEvent* event) override;

    /**
     * @brief      When the mouse leaves the widget event handler.
     *
     * @param      event  The event
     */
    void leaveEvent(QEvent* event) override;

    /**
     * @brief      Loads graphics.
     */
    void loadGraphics();

    /**
     * @brief      Sets up the UI.
     */
    void setupUi();

    QString id;
    QString name;

    QList<QSvgRenderer*> defaultFilters;
    QList<QSvgRenderer*> hoverFilters;
    QSvgRenderer* labelRenderer;
    QRectF labelRect;
    QPixmap background;

    bool isHovered = false;
};

/**
 * @brief      This class describes a new game menu.
 */
class NewGameMenu : public ScalableWidget
{
    Q_OBJECT

    public:
        /**
         * @brief      Creates a new game menu instance.
         *
         * @param      parent  The parent
         */
        NewGameMenu(QWidget *parent = nullptr);

        /**
         * @brief      Destroys the object.
         */
        ~NewGameMenu();

    signals:
        /**
         * @brief      Emitted when the new game menu is closed.
         */
        void newGameMenuClosed();

        /**
         * @brief      Emitted when a level is selected.
         *
         * @param[in]  id    The identifier
         */
        void levelSelected(const QString& id);

    private slots:
        /**
         * @brief      Called when new game menu closed.
         */
        void onNewGameMenuClosed();

    private:
        /**
         * @brief      Displays the available levels.
         */
        void displayLevels();

        /**
         * @brief      Sets up the UI.
         */
        void setupUi();

        /**
         * Columns for the grid.
         */
        const int columns = 2;

        QList<QString> levelJsons;
        QList<LevelInfoWidget*> levelButtons;
        QWidget* levelsWidget;
        QGridLayout* levelsLayout;

        QPushButton* backButton;
};