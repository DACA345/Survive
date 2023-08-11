#pragma once
#include <QGridLayout>
#include <QPushButton>

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
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

    void setupUi();

    QString id;
    QString name;
    QPixmap background;
};


class NewGameMenu : public ScalableWidget
{
    Q_OBJECT

    public:
        NewGameMenu(QWidget *parent = nullptr);
        ~NewGameMenu();

    signals:
        void newGameMenuClosed();

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