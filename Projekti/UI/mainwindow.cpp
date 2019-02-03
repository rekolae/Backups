#include "mainwindow.hh"

const int PAWN_AMOUNT = 3;

/*
 * TODO:
 * Actoreiden liikuttaminen (Roope) -Valmis
 * Transporttien liikuttaminenn (Roope) -Valmis
 * Kiekko grafiikka (Emil) <- VALMIS
 * Yksikkötestit IgamesStateen (Roope) <- valmis
 * Gameboard läpäsee valmiit yksikkötestit (Roope) -Valmis
 * Pisteytys ja tavoite (Roope) -Valmis
 * Pelin tilan seuranta (Roope) -Valmis
 * Ítsetehdyt yksikkötestit osaksi CI-ympäristöö (Emil) <- Valmis
 * Selviää virheellisistä asetustiedoista (Emil) <- VALMIS
 * Pawnien alustus (Emil) <- VALMIS
 * help button, josta pelin ohjeet uudessa ikkunassa (Emil) <-Valmis
 * Pelin lopetus. Tarkisat onko peli ohi ja näytä voittaja. (Emil) <- Valmis
 * Skippaa fliptile tarvittaessa (Roope) -Valmis
 */

namespace Student{

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    connect(configDialog_, &Dialog::configParameters,
            this, &MainWindow::configState);

    connect(errorDialog_, &ErrorDialog::exitGame,
            this, &MainWindow::exitGame);

    connect(boardScene_, &myGraphicsScene::cubeClicked,
            this, &MainWindow::HexClicked);

    connect(gameOverDialog_, &GameOverdDialog::gameOver,
            this, &MainWindow::quitGame);

    configDialog_->exec();
    gameState_->changePlayerTurn(0);
    board_->addBoardScene(boardScene_);

    //Try to initialize game and executes error dialog, if it fails
    try {
        runner_ = Common::Initialization::getGameRunner
                (board_,gameState_,playerVector_);
    }

    catch (Common::IoException){
        errorDialog_->errorMode(0);
        errorDialog_->exec();
    }

    //Try to read instruction text file and executes error dialog, if it fails.
    try {
        helpDialog_->readHelpFile();
    }

    catch (Common::IoException){
        errorDialog_->errorMode(1);
        errorDialog_->exec();
    }
}


void MainWindow::setupLayout()
{
    //Frame for UI
    frame_ = new QFrame;
    auto* gridLayout = new QGridLayout(this);
    auto* PawnOptionsGridLayout = new QGridLayout(this);
    auto* nameGrid = new QGridLayout(this);

    frame_->setLayout(gridLayout);

    //View for board scene
    auto* boardView = new QGraphicsView;
    boardView->setScene(boardScene_);
    boardView->setStyleSheet("QGraphicsView {background: gray;}");

    int sceneSizeX = 1100;
    int sceneSizeY = 1000;
    boardScene_->setSceneRect(0, 0, sceneSizeX,sceneSizeY);

    //Wheel scene
    auto* wheelView = new QGraphicsView;
    wheelView->setScene(wheelScene_);

    int wheelSceneSizeX = 150;
    int wheelSceneSizeY = 120;
    wheelScene_->setSceneRect(0, 0, wheelSceneSizeX,wheelSceneSizeY);


    QPushButton* closeButton = new QPushButton("Close game", this);
    QPushButton* helpButton = new QPushButton("Help", this);
    spinButton_->setEnabled(false);

    //PLayer info labels
    QLabel* playersLabel = new QLabel("Players:", this);
    QLabel* pawnsLeftLabel = new QLabel("Pawns:", this);
    QLabel* actionsLeftLabel = new QLabel("Actions:", this);
    QLabel* pointsLabel = new QLabel("Points:", this);

    for (unsigned int i = 0; i < playerAmount_; ++i) {
        QString name = QString::fromStdString(playerNames_.at(i));
        QLabel* playerName = new QLabel(name, this);
        QLabel* nameArrow = new QLabel(">", this);
        playerNameLabels.push_back(playerName);
        playerNameArrows.push_back(nameArrow);
    }

    connect(closeButton, &QPushButton::clicked,this, &MainWindow::close);
    connect(helpButton, &QPushButton::clicked,this,&MainWindow::helpClicked);
    connect(startButton_, &QPushButton::clicked,this, &MainWindow::startGame);
    connect(spinButton_, &QPushButton::clicked,this, &MainWindow::spinWheel);
    connect(skipPhaseButton_, &QPushButton::clicked, this,
            &MainWindow::skipPhase);


    startButton_->setStyleSheet("background-color:green");
    closeButton->setStyleSheet("background-color:red");
    skipPhaseButton_->setEnabled(false);

    gridLayout->addWidget(boardView,0,0,7,6);
    gridLayout->addWidget(wheelView,0,6,2,2);
    gridLayout->addWidget(spinButton_,2,6,1,2);
    gridLayout->addWidget(startButton_,7,6,1,1);
    gridLayout->addWidget(helpButton,7,5,1,1);
    gridLayout->addWidget(closeButton,7,7,1,1);
    gridLayout->addLayout(nameGrid,3,6,1,1);
    gridLayout->addWidget(hexInfoLabel_,7,0,1,1);
    gridLayout->addLayout(PawnOptionsGridLayout,7,1,1,1);
    gridLayout->addWidget(gamestateLabel_,4,6,1,2);
    gridLayout->addWidget(feedbackLabel_,5,6,1,2);
    gridLayout->addWidget(skipPhaseButton_,6,6,1,2);

    nameGrid->addWidget(playersLabel,0,0,1,1);
    nameGrid->addWidget(pawnsLeftLabel,0,3,1,1);
    nameGrid->addWidget(actionsLeftLabel,0,4,1,1);
    nameGrid->addWidget(pointsLabel,0,5,1,1);

    for(unsigned int i = 0; i < playerAmount_ ; ++i){
        nameGrid->addWidget(playerPawnAmountLabels_.at(i),1+i,3,1,1);
        nameGrid->addWidget(playerActionsLabels_.at(i),1+i,4,1,1);
        nameGrid->addWidget(pointsLabels_.at(i),1+i,5,1,1);

        playerPawnAmountLabels_.at(i)->setAlignment({Qt::AlignRight,
                                                     Qt::AlignVCenter});
        playerPawnAmountLabels_.at(i)->setText("0");
        playerActionsLabels_.at(i)->setAlignment({Qt::AlignRight,
                                                  Qt::AlignVCenter});
        playerActionsLabels_.at(i)->setText("0");

        pointsLabels_.at(i)->setAlignment({Qt::AlignRight,Qt::AlignVCenter});
        pointsLabels_.at(i)->setText("0");
    }

    int numberOfPawnButtons = 3;

    //Pawn comtrol buttons
    for(unsigned int i = 0; i < numberOfPawnButtons; ++i){
        PawnOptionsGridLayout->addWidget(pawnMoveButtons_.at(i),i,1,1,1);
        PawnOptionsGridLayout->addWidget(pawnLabels_.at(i),i,0,1,1);
        PawnOptionsGridLayout->addWidget(pawnBoatButtons_.at(i),i,2,1,1);
        PawnOptionsGridLayout->addWidget(treasureButtons_.at(i),i,3,1,1);
        PawnOptionsGridLayout->addWidget(pawnMoveTransportButtons_.at(i),i,4,1,1);

        connect(pawnMoveButtons_.at(i),&MyButton::movePawn,this,
                &MainWindow::movePawnSlot);
        connect(pawnBoatButtons_.at(i),&MyButton::movePawn,this,
                &MainWindow::enterBoatSlot);
        connect(treasureButtons_.at(i),&MyButton::movePawn,this,
                &MainWindow::searchForTreasure);
        connect(pawnMoveTransportButtons_.at(i),&MyButton::movePawn,this,
                &MainWindow::moveBoatSlot);

        pawnMoveButtons_.at(i)->hide();
        pawnLabels_.at(i)->hide();
        pawnBoatButtons_.at(i)->hide();
        treasureButtons_.at(i)->hide();
        pawnMoveTransportButtons_.at(i)->hide();
    }

    //Sets player name label colors to match pawn colors
    for (unsigned int i = 0; i < playerAmount_; ++i) {
        nameGrid->addWidget(playerNameArrows.at(i),1+i,1,1,1);
        nameGrid->addWidget(playerNameLabels.at(i),1+i,2,1,1);
        playerNameArrows.at(i)->hide();

        if (i == 0){
            playerNameLabels.at(i)->setStyleSheet("QLabel {color: yellow;}");
        }

        if (i == 1){
            playerNameLabels.at(i)->setStyleSheet("QLabel {color: lightgreen;}");
        }

        if (i == 2){
            playerNameLabels.at(i)->setStyleSheet("QLabel {color: cyan;}");
        }

        if (i == 3){
            playerNameLabels.at(i)->setStyleSheet("QLabel {color: red;}");
        }
    }

    playerNameArrows.at(0)->show();
    setCentralWidget(frame_);
}



void MainWindow::setupGameboard()
{
    for(unsigned int i = 0; i < playerAmount_ ; ++i){

        playerVector_.push_back(std::make_shared<Player>(i));
        playerVector_.at(i)->setActionsLeft(3);
    }
}



void MainWindow::startGame()
{
    startButton_->setEnabled(false);
    skipPhaseButton_->setEnabled(true);

    //Setup pawns
    for (int x = 0; playerAmount_ > x; ++x) {

        int pawnId;

        for (int y = 0; PAWN_AMOUNT > y; ++y) {
            if (x == 0) {
                board_->addPawn(x,y,Common::CubeCoordinate(-2,2,0));
            }

            if (x == 1) {
                pawnId = y+3;
                board_->addPawn(x,pawnId,Common::CubeCoordinate(2,-2,0));
            }

            if (x == 2) {
                pawnId = y+6;
                board_->addPawn(x,pawnId,Common::CubeCoordinate(0,-2,2));
            }

            if (x == 3) {
                pawnId = y+9;
                board_->addPawn(x,pawnId,Common::CubeCoordinate(0,2,-2));
            }
        }
    }

    setGamePhase(Common::MOVEMENT);
    updatePlayerInfo();
}


void MainWindow::spinWheel(){
    spinButton_->setEnabled(false);

    std::pair<std::string,std::string> actorPair = runner_->spinWheel();
    actorToMove_ = actorPair.first;
    actorMoveAmount_ = actorPair.second;
    wheelSpun_ = true;


    //Get actors that are same type as the one randomized by the wheel
    std::vector<std::shared_ptr<Common::Actor>> actorsOfType = board_->
            actorsOfType(actorToMove_);
    std::vector<std::shared_ptr<Common::Transport>> transportsOfType = board_->
            transportsOfType(actorToMove_);

    //Actors/transport of given type found
    if(!actorsOfType.empty() || !transportsOfType.empty()){
        displayInSpinWheel(actorToMove_, actorMoveAmount_);
        std::string text = "Move " + actorToMove_ + " by " + actorMoveAmount_;
        text += "\n click hex with " + actorToMove_ +
                " and then \n click hex where you want it to move";
        gamestateLabel_->setText(QString::fromStdString(text));
        feedbackLabel_->addText("Move given actor");
    }

    //Actors/transport of given type not found -> skip phase
    else{
        feedbackLabel_->addText("Randomized actors not in the game. "
                                "Skipping move actor phase");
        setGamePhase(Common::MOVEMENT);
        setNextPlayer();
    }

}


void MainWindow::configState(bool success, std::vector<std::string> names)
{
    if (success) {
        playerNames_ = std::move(names);
        playerAmount_ = playerNames_.size();
        configDialog_->close();

        setupLayout();
        setupGameboard();
    }

    else {
        exitGame();
    }
}


void MainWindow::HexClicked(Common::CubeCoordinate cubeCord)
{
    hexClickedBefore_ = hexClicked_;
    hexClicked_ = cubeCord;

    hidePawnButtons();

    //User wants to move pawns
    if(runner_->currentGamePhase() == Common::MOVEMENT){
        movePawns();
    }

    //Wheel has been spun -> move actors/transports
    else if(runner_->currentGamePhase() == Common::SPINNING && wheelSpun_){
        moveActors();
    }

    //flip tile
    else if(runner_->currentGamePhase() == Common::SINKING){
        flipTile();
    }
    //Show correct buttons and info about selected hex
    showPawnButtons();

    board_->makeHexSelected(cubeCord);

    std::vector<std::shared_ptr<Common::Actor>> actorVector = board_->
            getHex(hexClicked_)->getActors();
    std::vector<std::shared_ptr<Common::Transport>> transportVector = board_->
            getHex(hexClicked_)->getTransports();

    std::string text = "Type: ";
    text += board_->getHex(cubeCord)->getPieceType() + "\n";
    text += "Pawns: ";
    text += std::to_string(board_->checkTileOccupation(cubeCord)) +"\n";
    text += "Actors: ";
    for(const auto& actor : actorVector){
        text += actor->getActorType() + ", ";
    }
    text += "\n";
    text += "Transports: " + std::to_string(transportVector.size());
    hexInfoLabel_->clear();
    hexInfoLabel_->setText( QString::fromStdString(text));
}


void MainWindow::movePawnSlot(int pawnIndex)
{
    moveButtonClicked_ = true;
    moveBoatButtonClicked_ = false;
    moveButtonNumber_ = pawnIndex;
}


void MainWindow::enterBoatSlot(int pawnIndex)
{
    std::vector<std::shared_ptr<Common::Transport>> transports =
            board_->getHex(hexClicked_)->getTransports();
    std::vector<std::shared_ptr<Common::Pawn>> playersPawnsInHex =
            board_->getPlayersPawnsInHex(hexClicked_,gameState_->
                                         currentPlayer());

    //Add pawn in transport if it is not in one
    if(!transports.at(0)->isPawnInTransport(playersPawnsInHex.at(pawnIndex))
            && transports.at(0)->getCapacity() >= 1){

        transports.at(0)->addPawn(playersPawnsInHex.at(pawnIndex));
        pawnBoatButtons_.at(pawnIndex)->setText("Leave transport");
        pawnLabels_.at(pawnIndex)->setText("Pawn (in transport)");
        pawnMoveTransportButtons_.at(pawnIndex)->show();

        if(!transports.at(0)->canMove(gameState_->currentPlayer())){
            pawnMoveButtons_.at(pawnIndex)->setEnabled(false);
            pawnMoveTransportButtons_.at(pawnIndex)->hide();
        }
    }

    //remove pawn from transport
    else{
        transports.at(0)->removePawn(playersPawnsInHex.at(pawnIndex));
        pawnBoatButtons_.at(pawnIndex)->setText("Enter transport");
        pawnLabels_.at(pawnIndex)->setText("Pawn");
        pawnMoveButtons_.at(pawnIndex)->setEnabled(true);
        pawnMoveTransportButtons_.at(pawnIndex)->hide();
    }
}


void MainWindow::searchForTreasure()
{
    if(playerVector_.at(gameState_->currentPlayer())->getActionsLeft() > 0){
        if(!board_->getHex(hexClicked_)->isWaterTile()){
            srand (time(nullptr));
            int randomInt= rand() % 10 + 1;

            //50% change to find a treasure
            if(randomInt < 5){
                addPoints({gameState_->currentPlayer(),10});
                feedbackLabel_->addText("Found a treasure");
            }

            else{
                feedbackLabel_->addText("Didn't find a treasure");
            }

            playerVector_.at(gameState_->currentPlayer())->
                    setActionsLeft(playerVector_.at(gameState_->
                            currentPlayer())->getActionsLeft() -1);
            updatePlayerInfo();
        }
    }
    else{
        feedbackLabel_->addText("No actions left");
    }

    //Change gamephase if player run out of actions
    if(playerVector_.at(gameState_->currentPlayer())->getActionsLeft() == 0){
        setGamePhase(Common::SINKING);
    }
}


void MainWindow::moveBoatSlot(int pawnIndex)
{
    moveButtonClicked_ = false;
    moveBoatButtonClicked_ = true;

    std::vector<std::shared_ptr<Common::Pawn>> playersPawnsInHex =
            board_->getPlayersPawnsInHex(hexClicked_,gameState_->currentPlayer());

    std::vector<std::shared_ptr<Common::Transport>> transports =
            board_->getHex(hexClicked_)->getTransports();

    for(const auto& transport : transports){
        if(transport->isPawnInTransport(playersPawnsInHex.at(pawnIndex))){
            boatToMove = transport->getId();
        }
    }
}


void MainWindow::skipPhase()
{
    feedbackLabel_->addText("Skipping phase");
    if(gameState_->currentGamePhase() == Common::MOVEMENT){
        setGamePhase(Common::SINKING);
    }

    else if(gameState_->currentGamePhase() == Common::SINKING){
        setGamePhase(Common::SPINNING);
        spinButton_->setEnabled(true);
    }

    else{
        spinButton_->setEnabled(false);
        setGamePhase(Common::MOVEMENT);
        setNextPlayer();
    }
}



void MainWindow::quitGame()
{
    exitGame();
}



void MainWindow::helpClicked()
{
    helpDialog_->exec();
}


void MainWindow::exitGame()
{
    exit(EXIT_SUCCESS);
}



void MainWindow::setGamePhase(Common::GamePhase phase)
{
    //Check if game is over
    if (CheckIfGameOver()) {
        std::map<int, std::string> results;
        for (unsigned int i = 0; playerAmount_ > i; ++i) {
            results[points_.at(i)] = playerNames_.at(i);
        }

        gameOverDialog_->displayData(results, points_);
        gameOverDialog_->exec();
    }

    else {
        updatePlayerInfo();

        //If there are no tiles to flip, skip the tile flip phase.
        if(board_->getHex(Common::CubeCoordinate(0,0,0))->isWaterTile()
                && phase == Common::SINKING){
            feedbackLabel_->addText("Skipping tile flip phase");
            gameState_->changeGamePhase(Common::SPINNING);
            phase = Common::SPINNING;
            spinButton_->setEnabled(true);
        }
        else{
            gameState_->changeGamePhase(phase);
        }

        std::string text ="Gamephase " + std::to_string(phase);

        //Set next gamephase
        if(phase == Common::MOVEMENT){
            text += ": Move your pawns";
            wheelScene_->clear();
        }

        else if(phase == Common::SINKING){
            text +=": Choose a tile to sink";
        }

        else {
            text +=": Spin the wheel";
        }

        gamestateLabel_->setText(QString::fromStdString(text));
    }
}



void MainWindow::setNextPlayer()
{
    feedbackLabel_->addText("Player turn has changed");
    int currentPlayer = gameState_->currentPlayer();
    currentPlayer ++;
    if(currentPlayer == playerAmount_){
        currentPlayer = 0;
    }

    gameState_->changePlayerTurn(currentPlayer);
    playerVector_.at(currentPlayer)->setActionsLeft(3);

    for(auto arrow : playerNameArrows){
        arrow->hide();
    }

    playerNameArrows.at(currentPlayer)->show();
    updatePlayerInfo();
}



void MainWindow::displayInSpinWheel(const std::string& actor,
                                    const std::string& amount)
{    
    QPixmap actorPix;
    QPixmap numberPix;

    if (actor == "shark") {
        if (actorPix.load(":/actorImages/shark.png")) {
        }
    }

    if (actor == "kraken") {
        if (actorPix.load(":/actorImages/kraken.png")) {
        }
    }

    if (actor == "dolphin") {
        if (actorPix.load(":/actorImages/dolphin.png")) {
        }
    }

    if (actor == "seamunster") {
        if (actorPix.load(":/actorImages/seamonster.png")) {
        }
    }

    if (amount == "1") {
        if (numberPix.load(":/actorImages/1.png")) {
        }
    }

    if (amount == "2") {
        if (numberPix.load(":/actorImages/2.png")) {

        }
    }

    if (amount == "3") {
       if (numberPix.load(":/actorImages/3.png")) {

        }
    }

    if (amount == "D") {
        if (numberPix.load(":/actorImages/D.png")) {
        }
    }

    QPixmap newPixmap = actorPix.scaled(QSize(100,100),  Qt::KeepAspectRatio);
    QPixmap newPixmap2 =numberPix.scaled(QSize(100,100),  Qt::KeepAspectRatio);

    auto* actorImage = new QGraphicsPixmapItem(newPixmap);
    auto* numberImage = new QGraphicsPixmapItem(newPixmap2);


    wheelScene_->addItem(actorImage);
    wheelScene_->addItem(numberImage);

    actorImage->setPos(-50, 0);
    numberImage->setPos(50, 0);
}


void MainWindow::updatePlayerInfo()
{
    for(unsigned int i = 0; i < playerAmount_ ; ++i){
        playerPawnAmountLabels_.at(i)->setText(QString::fromStdString(
                                    std::to_string(board_->
                                                   amountOfPlayerOwnedPawns(i))));

        playerActionsLabels_.at(i)->setText(QString::fromStdString(
                                    std::to_string(playerVector_.at(i)->
                                                   getActionsLeft())));

        pointsLabels_.at(i)->setText(QString::fromStdString(
                                         std::to_string(points_.at(i))));
    }
}


void MainWindow::addPoints(std::pair<int, int> pair)
{
    if(pair.first != -1){
        points_.at(pair.first) += pair.second;
        if(pair.second == 100){
            feedbackLabel_->addText("Congratulations, you saved a pawn");
        }
    }
    updatePlayerInfo();
}



void MainWindow::hidePawnButtons()
{
    int numberOfPawnButtons = 3;
    for(unsigned int i = 0; i<numberOfPawnButtons; ++i){
        pawnMoveButtons_.at(i)->hide();
        pawnLabels_.at(i)->hide();
        pawnBoatButtons_.at(i)->hide();
        treasureButtons_.at(i)->hide();
        pawnMoveTransportButtons_.at(i)->hide();
        pawnBoatButtons_.at(i)->setText("Enter transport");
        pawnLabels_.at(i)->setText("Pawn");
        pawnMoveButtons_.at(i)->setText("Move");
        pawnMoveButtons_.at(i)->setEnabled(true);
        treasureButtons_.at(i)->setEnabled(true);
    }
}



void MainWindow::showPawnButtons()
{
    std::vector<std::shared_ptr<Common::Transport>> transports =
            board_->getHex(hexClicked_)->getTransports();
    std::vector<std::shared_ptr<Common::Pawn>> playersPawnsInHex =
            board_->getPlayersPawnsInHex(hexClicked_,gameState_->
                                         currentPlayer());

    for(unsigned int i = 0; i<playersPawnsInHex.size(); ++i){
        pawnMoveButtons_.at(i)->show();
        pawnLabels_.at(i)->show();
        treasureButtons_.at(i)->show();

        if(!transports.empty()){
            pawnBoatButtons_.at(i)->show();

            if(transports.at(0)->isPawnInTransport(playersPawnsInHex.
                                                   at(i))){
                pawnBoatButtons_.at(i)->setText("Leave transport");
                pawnLabels_.at(i)->setText("Pawn (in transport)");
                pawnMoveTransportButtons_.at(i)->show();

                if(!transports.at(0)->canMove(gameState_->
                                              currentPlayer())){
                    pawnMoveButtons_.at(i)->setEnabled(false);
                }
            }
        }

        if(board_->getHex(hexClicked_)->isWaterTile()){
            treasureButtons_.at(i)->setEnabled(false);
        }
    }
}


void MainWindow::movePawns()
{
    std::vector<std::shared_ptr<Common::Transport>> transports =
            board_->getHex(hexClicked_)->getTransports();

    //Move pawns
    if(moveButtonClicked_ && !moveBoatButtonClicked_){
        std::vector<std::shared_ptr<Common::Pawn>> playersPawnsInHex =
                board_->getPlayersPawnsInHex(hexClickedBefore_,gameState_->
                                             currentPlayer());
        try{
            int actionsLeft = runner_->
                    movePawn(hexClickedBefore_,hexClicked_,
                             playersPawnsInHex.at(moveButtonNumber_)->
                             getId());
            addPoints(board_->checkGoals(hexClicked_));

            if(actionsLeft != -1){
                playerVector_.at(runner_->currentPlayer())->
                        setActionsLeft(actionsLeft);
                feedbackLabel_->addText("Moved a pawn");
            }

            if(actionsLeft == 0){
                setGamePhase(Common::SINKING);
            }

            moveButtonClicked_ = false;
        }

        catch(Common::IllegalMoveException const &msg){
            moveButtonClicked_ = false;
            feedbackLabel_->addText(msg.msg());
        }
        updatePlayerInfo();
    }

    //Move transports
    if(moveBoatButtonClicked_ && !moveButtonClicked_){

        try {
            int movesLeft = runner_->moveTransport(hexClickedBefore_,
                                                   hexClicked_,boatToMove);

            board_->setPawnGraphicsPosition(hexClicked_);
            updatePlayerInfo();

            if(movesLeft == 0){
                setGamePhase(Common::SINKING);
            }

        } catch (Common::IllegalMoveException const &msg) {
            feedbackLabel_->addText(msg.msg());
        }

        moveBoatButtonClicked_ = false;

    }
}


void MainWindow::moveActors()
{
    std::vector<std::shared_ptr<Common::Actor>> actorsOfType = board_->
            actorsOfType(actorToMove_);
    std::vector<std::shared_ptr<Common::Transport>> transportsOfType =
            board_->transportsOfType(actorToMove_);
    std::shared_ptr<Common::Actor> chosenActor;
    std::shared_ptr<Common::Transport> chosenTransport;

    try{
        for(const auto& actor : actorsOfType){
            if(actor->getHex()->getCoordinates() == hexClickedBefore_ &&
                    actor->getActorType() == actorToMove_){
                chosenActor = actor;
            }
        }

        for(const auto& transport : transportsOfType){
            if(transport->getHex()->getCoordinates() == hexClickedBefore_ &&
                    transport->getTransportType() == actorToMove_){
                chosenTransport = transport;
            }
        }

        //Move actors
        if(chosenActor != nullptr){
            runner_->moveActor(hexClickedBefore_,hexClicked_,chosenActor->
                               getId(),actorMoveAmount_);
            chosenActor->doAction();
            feedbackLabel_->addText(chosenActor->
                                    getActorType() + " has moved");

            feedbackLabel_->addText(chosenActor->
                                    getActorType() + " does an action");

            board_->clearGraphics(hexClicked_,chosenActor->getActorType());
            setNextPlayer();
            setGamePhase(Common::MOVEMENT);
            if(board_->amountOfPlayerOwnedPawns(gameState_->
                                                currentPlayer()) == 0){
                setGamePhase(Common::SINKING);
            }
            wheelSpun_ = false;
        }

        //Move transports
        if(chosenTransport != nullptr){
            runner_->moveTransportWithSpinner(hexClickedBefore_,
                                              hexClicked_,chosenTransport->
                                              getId(),actorMoveAmount_);
            board_->setPawnGraphicsPosition(hexClicked_);
            setNextPlayer();
            setGamePhase(Common::MOVEMENT);
            if(board_->amountOfPlayerOwnedPawns(gameState_->
                                                currentPlayer()) == 0){
                setGamePhase(Common::SINKING);
            }
            wheelSpun_ = false;
        }
    }

    catch(Common::IllegalMoveException const &msg){
        feedbackLabel_->addText(msg.msg());
    }
}


void MainWindow::flipTile()
{
    try{
        std::string actor = runner_->flipTile(hexClicked_);
        if(!actor.empty()){
            feedbackLabel_->addText(actor + " has spawned in");
            setGamePhase(Common::SPINNING);
            spinButton_->setEnabled(true);
            std::vector<std::shared_ptr<Common::Actor>> actors = board_->
                    getHex(hexClicked_)->getActors();

            for(const auto& actor : actors){
                feedbackLabel_->addText(actor->getActorType() +
                                        " does action");
                actor->doAction();
                board_->clearGraphics(hexClicked_,actor->getActorType());

            }
        }
    }

    catch(Common::IllegalMoveException const &msg){
        feedbackLabel_->addText(msg.msg());
    }

}


bool MainWindow::CheckIfGameOver()
{
    for (int i = 0; playerAmount_ > i; i++) {

        //If there is atleast one pawn on the gameboard, the game continues
        if (board_->amountOfPlayerOwnedPawns(i) != 0) {
            gameOver_ = false;
            break;
        }

        else {
            gameOver_ = true;
        }
    }

    return gameOver_;
}

}
