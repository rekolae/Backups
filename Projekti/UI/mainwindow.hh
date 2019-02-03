#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameengine.hh"
#include "mygraphicsscene.hh"
#include "cubecoordinate.hh"
#include "gamestate.hh"
#include "player.hh"
#include "iconmaker.hh"
#include "mybutton.hh"
#include "mylabel.h"
#include "gameoverddialog.hh"
#include "helpdialog.hh"
#include "gameboard.hh"
#include "dialog.hh"
#include "errordialog.hh"
#include "illegalmoveexception.hh"
#include "ioexception.hh"
#include "initialize.hh"
#include "hex.hh"
#include "iplayer.hh"

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFrame>
#include <QLabel>
#include <vector>
#include <QPushButton>
#include <QPixmap>
#include <QBoxLayout>
#include <iostream>
#include <cmath>
#include <memory>
#include <QLayout>
#include <QDialog>
#include <QCoreApplication>
#include <algorithm>
#include <iterator>
#include <utility>
#include <QGridLayout>
#include <QPainter>
#include <QPolygonF>
#include <QGraphicsPolygonItem>

namespace Student{

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * @brief MainWindow Constructor.
     * @param parent Parent widget.
     */
    explicit MainWindow(QWidget *parent = nullptr);

    std::vector<QLabel*>playerNameLabels;
    std::vector<QLabel*>playerNameArrows;

public slots:

    /**
     * @brief startGame. Setups pawns.
     */
    void startGame();

    /**
     * @brief spinWheel Gets the that that is to be moved.
     */
    void spinWheel();

    /**
     * @brief configState Checks if there was errors during configuration.
     * @param success_ True if config succeeded.
     * @param names Holds the names of the players.
     */
    void configState(bool success_ = false, std::vector<std::string> names = {});

    /**
     * @brief HexClicked Handels the user input and runs the game.
     * @param cubeCord Coordinates of the hex clicked.
     */
    void HexClicked(Common::CubeCoordinate cubeCord);

    /**
     * @brief movePawnSlot Slot for moving pawns.
     * @param pawnIndex index of pawn in the hex.
     */
    void movePawnSlot(int pawnIndex);

    /**
     * @brief enterBoatSlot Adds and removes pawns from transports.
     * @param pawnIndex index of pawn in the hex.
     */
    void enterBoatSlot(int pawnIndex);

    /**
     * @brief searchForTreasure Searches for treasure. 50% change find one.
     * @param pawnIndex Pawn's index.
     */
    void searchForTreasure();

    /**
     * @brief moveBoatSlot Used to move transports when pawn is in them.
     * @param pawnIndex Index of pawn.
     */
    void moveBoatSlot(int pawnIndex);

    /**
     * @brief skipPhase Skips current phase.
     */
    void skipPhase();

    /**
     * @brief quitGame Quits the game.
     */
    void quitGame();

    /**
     * @brief helpClicked Opens help window.
     */
    void helpClicked();

private:

    /**
     * @brief setupLayout Setups layout for mainwindow.
     */
    void setupLayout();

    /**
     * @brief setupGameboard Saves players.
     */
    void setupGameboard();

    /**
     * @brief exitGame Exits game.
     */
    void exitGame();

    /**
     * @brief setGamePhase Sets current game phase.
     * @param phase game phase to set.
     */
    void setGamePhase(Common::GamePhase phase);

    /**
     * @brief setNextPlayer Sets next player.
     */
    void setNextPlayer();

    /**
     * @brief displayInSpinWheel Displays actor randomized by the wheel.
     * @param actor Actor type.
     * @param Amount Amount of moves (1, 2, 3, D).
     */
    void displayInSpinWheel(const std::string& actor,
                            const std::string& Amount);

    /**
     * @brief updatePlayerInfo Updates player info that is shown.
     */
    void updatePlayerInfo();

    /**
     * @brief addPoints Adds points to player.
     * @param pair <Player Id, points>.
     */
    void addPoints(std::pair<int,int> pair);

    /**
     * @brief hidePawnButtons Hides all pawn buttons.
     */
    void hidePawnButtons();

    /**
     * @brief showPawnButtons Shows all pawn buttons.
     */
    void showPawnButtons();

    /**
     * @brief movePawns Moves pawn.
     */
    void movePawns();

    /**
     * @brief moveActors Moves actor.
     */
    void moveActors();

    /**
     * @brief flipTile flips tile.
     */
    void flipTile();

    /**
     * @brief CheckIfGameOver Checks if game has ended.
     * @return True if game over, false if not.
     */
    bool CheckIfGameOver();

    std::shared_ptr<Student::IconMaker> iconMaker_ =
            std::make_shared<Student::IconMaker>();
    std::shared_ptr<Common::IGameRunner> runner_;
    std::shared_ptr<Student::GameBoard> board_ =
            std::make_shared<Student::GameBoard>();
    QGraphicsScene* wheelScene_ = new QGraphicsScene;
    myGraphicsScene* boardScene_ = new myGraphicsScene(this);
    std::shared_ptr<GameState> gameState_ = std::make_shared<GameState>();

    //Layout stuff
    QFrame* frame_;

    //Player containers
    unsigned int playerAmount_;
    std::vector<std::string> playerNames_;    
    std::vector<std::shared_ptr<Common::IPlayer>> playerVector_;

    //Dialog windows
    Dialog* configDialog_ = new Dialog;
    ErrorDialog* errorDialog_ = new ErrorDialog;
    GameOverdDialog* gameOverDialog_ = new GameOverdDialog;
    HelpDialog* helpDialog_ = new HelpDialog;

    //All labels and label containers
    QLabel* hexInfoLabel_ = new QLabel(this);
    QLabel* pawn1Label_ = new QLabel("Pawn ", this);
    QLabel* pawn2Label_ = new QLabel("Pawn ", this);
    QLabel* pawn3Label_ = new QLabel("Pawn ", this);
    QLabel* gamestateLabel_ = new QLabel(this);
    myLabel* feedbackLabel_ = new myLabel(this);
    std::vector<QLabel*> pawnLabels_ = {pawn1Label_,pawn2Label_,pawn3Label_};
    std::vector<QLabel*> actorLabels_;
    std::vector<QLabel*> playerPawnAmountLabels_ =
        {new QLabel(this),new QLabel(this),new QLabel(this),new QLabel(this)};
    std::vector<QLabel*> playerActionsLabels_ =
        {new QLabel(this),new QLabel(this),new QLabel(this),new QLabel(this)};
    std::vector<QLabel*> pointsLabels_ =
        {new QLabel(this),new QLabel(this),new QLabel(this),new QLabel(this)};

    //Buttons to interact with pawns
    MyButton* pawn1MoveButton_ = new MyButton("Move", this,0);
    MyButton* pawn2MoveButton_ = new MyButton("Move", this,1);
    MyButton* pawn3MoveButton_ = new MyButton("Move", this,2);

    MyButton* pawn1MoveTransportButton_ = new MyButton("Move transport", this,0);
    MyButton* pawn2MoveTransportButton_ = new MyButton("Move transport", this,1);
    MyButton* pawn3MoveTransportButton_ = new MyButton("Move transport", this,2);

    MyButton* pawn1BoatButton_ = new MyButton("Enter boat", this,0);
    MyButton* pawn2BoatButton_ = new MyButton("Enter boat", this,1);
    MyButton* pawn3BoatButton_ = new MyButton("Enter boat", this,2);

    MyButton* treasureButton1_ = new MyButton("Search for treasure", this,0);
    MyButton* treasureButton2_ = new MyButton("Search for treasure", this,1);
    MyButton* treasureButton3_ = new MyButton("Search for treasure", this,2);

    std::vector<MyButton*> pawnMoveButtons_ =
        {pawn1MoveButton_,pawn2MoveButton_,pawn3MoveButton_};
    std::vector<MyButton*> pawnMoveTransportButtons_ =
        {pawn1MoveTransportButton_,pawn2MoveTransportButton_,
         pawn3MoveTransportButton_};
    std::vector<MyButton*> pawnBoatButtons_ =
        {pawn1BoatButton_,pawn2BoatButton_,pawn3BoatButton_};
    std::vector<MyButton*> treasureButtons_ =
        {treasureButton1_,treasureButton2_,treasureButton3_};

    //Other buttons
    QPushButton* spinButton_ = new QPushButton("Spin wheel", this);
    QPushButton* skipPhaseButton_ = new QPushButton("Skip phase", this);
    QPushButton* startButton_ = new QPushButton("Start game", this);

    //Variables
    Common::CubeCoordinate hexClicked_;
    Common::CubeCoordinate hexClickedBefore_;

    bool moveButtonClicked_ = false;
    bool boatButtonClicked_ = false;
    bool moveBoatButtonClicked_ = false;

    int boatToMove = -1;
    int moveButtonNumber_;
    bool wheelSpun_ = false;
    bool gameOver_;

    std::string actorToMove_;
    std::string actorMoveAmount_;

    std::vector<int> points_ = {0,0,0,0};

};
}

#endif // MAINWINDOW_HH
