#pragma once
#include <QGridLayout>
#include <QPushButton>
#include <QSvgRenderer>

#include "../scalablewidget.h"

class LevelInfoWidget : public ScalableWidget
{
    Q_OBJECT

public:
    LevelInfoWidget(const QString& levelJson, QWidget* parent = nullptr);
    ~LevelInfoWidget();

signals:
    void levelSelected(const QString& levelName);

private:

    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;

    void setupUi();
    void loadGraphics();

    QString id;
    QString name;

    QList<QSvgRenderer*> defaultFilters;
    QList<QSvgRenderer*> hoverFilters;
    QSvgRenderer* labelRenderer;
    QRectF labelRect;
    QPixmap background;

    bool isHovered = false;
};


class NewGameMenu : public ScalableWidget
{
    Q_OBJECT

    public:
        NewGameMenu(QWidget *parent = nullptr);
        ~NewGameMenu();

    signals:
        void newGameMenuClosed();
        void levelSelected(const QString& id);

    private slots:
        void onNewGameMenuClosed();

    private:
        void displayLevels();
        void setupUi();

        const int columns = 2;

        QList<QString> levelJsons;
        QList<LevelInfoWidget*> levelButtons;
        QWidget* levelsWidget;
        QGridLayout* levelsLayout;

        QPushButton* backButton;
};