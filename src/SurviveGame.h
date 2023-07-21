#pragma once
#include <QMainWindow>

class SurviveGame : public QMainWindow
{
    Q_OBJECT

    public:
        explicit SurviveGame(QWidget* parent = nullptr);
        ~SurviveGame();
};