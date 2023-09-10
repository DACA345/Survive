#include <QPainter>

#include "game.h"
#include "../config/files.h"

#define ON_ACTION(action, engineAction) \
    void Game::on##action() \
    { \
        handleActionResult(engine.engineAction()); \
    }

Game::Game(const QString& levelId, QWidget *parent)
    : ScalableWidget(parent), engine(levelId)
{
    loadGraphics();
    setupUi();
    updateUi();
}

void Game::paintEvent(QPaintEvent* event)
{
    ScalableWidget::paintEvent(event);

    QPainter painter(this);

    painter.drawPixmap(rect(), background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

ON_ACTION(FindFood, findFood)
ON_ACTION(FindWater, findWater)
ON_ACTION(Explore, explore)
ON_ACTION(Rest, rest)

void Game::onResultAcknowledged()
{
    // Disable actions when turns used up
    if (engine.getTurns() <= 0)
    {
        notebookWidget->hide();
        sleepButton->show();
    }
}

void Game::nextDay()
{
    EventResult event = engine.nextDay();
    // NOTE(Callum): Temporary fix to display the event
    if (event.triggered)
    {
        notebookWidget->displayResultsWidget("Day Event", event.event.event);
    }

    updateUi();
}

void Game::loadGraphics()
{
    background = QPixmap(textureFile("set/image.png"));
}

void Game::setupUi()
{
    notebookButton = new SVGPushButton(TEXTURE_FILE("ui/notebook/icon.svg"), this);
    notebookButton->hide();
    notebookWidget = new NotebookWidget(engine, this);

    bars = new QSvgWidget(TEXTURE_FILE("ui/bars/bars.svg"), this);
    healthBarFill = new QSvgWidget(TEXTURE_FILE("ui/bars/fill/health.svg"), this);
    thirstBarFill = new QSvgWidget(TEXTURE_FILE("ui/bars/fill/thirst.svg"), this);
    hungerBarFill = new QSvgWidget(TEXTURE_FILE("ui/bars/fill/hunger.svg"), this);
    energyBarFill = new QSvgWidget(TEXTURE_FILE("ui/bars/fill/energy.svg"), this);

    sleepButton = new QPushButton("Sleep", this);
    sleepButton->hide();

    connect(notebookButton, &QPushButton::clicked, notebookWidget, &NotebookWidget::show);
    connect(notebookButton, &QPushButton::clicked, notebookButton, &SVGPushButton::hide);

    connect(notebookWidget, &NotebookWidget::findFood, this, &Game::onFindFood);
    connect(notebookWidget, &NotebookWidget::findWater, this, &Game::onFindWater);
    connect(notebookWidget, &NotebookWidget::explore, this, &Game::onExplore);
    connect(notebookWidget, &NotebookWidget::rest, this, &Game::onRest);

    connect(notebookWidget, &NotebookWidget::resultAcknowledged, this, &Game::onResultAcknowledged);

    connect(notebookWidget, &NotebookWidget::close, notebookButton, &SVGPushButton::show);

    connect(sleepButton, &QPushButton::clicked, this, &Game::nextDay);

    addWidget(notebookButton, 0.01, 0.85, 0.06, 0.14);
    addWidget(notebookWidget, 0.35, 0.125, 0.3, 0.75);

    addWidget(bars, 1 - 0.295, 0.01, 0.285, 0.2);

    addWidget(sleepButton, 0.45, 0.85, 0.1, 0.1);
}

void Game::updateBars()
{
    // Bar updates
#define UI_BAR_X 0.73
#define UI_BAR_WIDTH 0.26
#define UI_BAR_Y 0.011
#define UI_BAR_Y_GAP 0.01465
#define UI_BAR_HEIGHT 0.0385

    addWidget(healthBarFill, UI_BAR_X, UI_BAR_Y, UI_BAR_WIDTH * ((double) engine.getHealth() / (double) BAR_MAX), UI_BAR_HEIGHT);
    addWidget(thirstBarFill, UI_BAR_X, UI_BAR_Y + UI_BAR_Y_GAP + UI_BAR_HEIGHT, UI_BAR_WIDTH * ((double) engine.getThirst() / (double) BAR_MAX), UI_BAR_HEIGHT);
    addWidget(hungerBarFill, UI_BAR_X, UI_BAR_Y + 2 * UI_BAR_Y_GAP + 2 * UI_BAR_HEIGHT, UI_BAR_WIDTH * ((double) engine.getHunger() / (double) BAR_MAX), UI_BAR_HEIGHT);
    addWidget(energyBarFill, UI_BAR_X, UI_BAR_Y + 3 * UI_BAR_Y_GAP + 3 * UI_BAR_HEIGHT, UI_BAR_WIDTH * ((double) engine.getEnergy() / (double) BAR_MAX), UI_BAR_HEIGHT);

}

void Game::updateUi()
{
    updateBars();

    if (engine.getTurns() > 0)
    {
        notebookWidget->show();
        sleepButton->hide();
    }

    notebookWidget->updateDay();
}

QString Game::textureFile(const QString& name)
{
    return TEXTURE_FILE(QString("levels/%1/%2").arg(engine.getLevel().getInfo().id).arg(name));
}

void Game::handleActionResult(ActionResult result)
{
    if (result.result == ActionBaseResult::NO_TURNS)
    {
        // Should never occur
        qFatal("No turns left");
        return;
    }
    else if (result.result == ActionBaseResult::GAME_OVER)
    {
        endGame();
    }
    else
    {
        notebookWidget->displayResultsWidget(result.action, result.message);
        updateUi();
    }
}

void Game::endGame()
{
    gameOver = new GameOver(this);
    gameOver->show();

    connect(gameOver, &GameOver::close, this, &Game::returnToMenu);

    addWidget(gameOver, 0, 0, 1, 1);
}

Game::~Game()
{
    if (gameOver)
    {
        delete gameOver;
    }

    delete notebookButton;
    delete notebookWidget;

    delete bars;
    delete healthBarFill;
    delete thirstBarFill;
    delete hungerBarFill;
    delete energyBarFill;
}

