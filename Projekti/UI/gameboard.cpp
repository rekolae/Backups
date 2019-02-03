#include "gameboard.hh"

namespace Student{

GameBoard::GameBoard()
= default;

GameBoard::~GameBoard()
= default;


int GameBoard::checkTileOccupation(Common::CubeCoordinate tileCoord) const
{
    std::shared_ptr<Common::Hex> tile = getHex(tileCoord);
    if(tile == nullptr){
        return -1;
    }

    return  tile->getPawnAmount();
}


bool GameBoard::isWaterTile(Common::CubeCoordinate tileCoord) const
{
    for(const std::shared_ptr<Common::Hex>& hex: hexVector_){
        if(hex->getCoordinates() == tileCoord){
            return hex->isWaterTile();
        }
    }

    return false;
}


std::shared_ptr<Common::Hex> GameBoard::getHex(Common::CubeCoordinate hexCoord) const
{
        for(std::shared_ptr<Common::Hex> hex : hexVector_){
            if(hex->getCoordinates() == hexCoord){
                return hex;
            }
        }

        return nullptr;
}


void GameBoard::addPawn(int playerId, int pawnId)
{
    std::shared_ptr<Common::Pawn> newPawn = std::make_shared<Common::Pawn>();
    newPawn->setId(pawnId,playerId);
    pawnMap_[pawnId] = newPawn;

    if(boardScene_ != nullptr){
        QGraphicsPolygonItem* item = iconMaker_->makePawnIcon(pawnId);
        pawnGraphicsMap_[pawnId] = item;
    }
}


void GameBoard::addPawn(int playerId, int pawnId, Common::CubeCoordinate coord)
{
    std::shared_ptr<Common::Pawn> newPawn =
            std::make_shared<Common::Pawn>(pawnId,playerId,coord);
    std::shared_ptr<Common::Hex> hex = getHex(coord);
    hex->addPawn(newPawn);
    pawnMap_[pawnId] = newPawn;

    if(boardScene_ != nullptr){
        QGraphicsPolygonItem* item = iconMaker_->makePawnIcon(playerId);
        pawnGraphicsMap_[pawnId] = item;
        boardScene_->addItem(item);
        setPawnGraphicsPosition(coord);
    }
}


void GameBoard::movePawn(int pawnId, Common::CubeCoordinate pawnCoord)
{
    std::shared_ptr<Common::Pawn> pawn = pawnMap_.at(pawnId);
    if(checkTileOccupation(pawnCoord) < 3){

        std::shared_ptr<Common::Hex> hex = getHex(pawnCoord);
        if(hex != nullptr){
            removePawn(pawnId);
            getHex(pawnCoord)->addPawn(pawn);
            pawn->setCoordinates(pawnCoord);
            if(boardScene_ != nullptr){
                setPawnGraphicsPosition(pawnCoord);
            }
        }
    }
}


void GameBoard::removePawn(int pawnId)
{
    if(pawnMap_.find(pawnId) != pawnMap_.end()) {
        std::shared_ptr<Common::Pawn> pawn = pawnMap_.at(pawnId);
        Common::CubeCoordinate currentCoord = pawn->getCoordinates();
        std::shared_ptr<Common::Hex> currentHex = getHex(currentCoord);
        currentHex->removePawn(pawn);
    }
}


void GameBoard::moveActor(int actorId, Common::CubeCoordinate actorCoord)
{
    if(getHex(actorCoord) != nullptr){
        actorMap_.at(actorId)->getHex()->removeActor(actorMap_.at(actorId));
        actorMap_.at(actorId)->addHex(getHex(actorCoord));
        if(boardScene_ != nullptr){
            setActorOrTransportGraphicsPosition(actorCoord);
        }
    }
}


void GameBoard::removeActor(int actorId)
{
    for(auto actor : actorMap_){
        if(actor.first == actorId){

            actor.second->getHex()->removeActor(actor.second);
            actorMap_.erase(actor.first);
            break;
        }
    }
}


void GameBoard::addHex(std::shared_ptr<Common::Hex> newHex)
{
    bool hexIsNew = true;
    for(int i=0; i < hexVector_.size();++i){
        if(hexVector_.at(i)->getCoordinates() == newHex->getCoordinates()){
            hexIsNew = false;
            hexVector_.erase(hexVector_.begin()+i);
        }
    }

    hexVector_.push_back(newHex);
    Common::CubeCoordinate cubeCord = newHex->getCoordinates();

    //Add graphics if hex is new
    if(hexIsNew){

        int sceneSizeXmiddle = 550;
        int sceneSizeYmiddle = 500;
        int hexSize = 30;
        int hexCornerAmount = 6;

        int x_pixel = sceneSizeXmiddle + (52 *cubeCord.z) + (26 * cubeCord.y)
                + (78*cubeCord.x);
        int y_pixel = sceneSizeYmiddle + (45 * -cubeCord.y)+ (45* -cubeCord.x);

        QPolygonF hexPoints;
        for(int i = 0; i < hexCornerAmount ; ++i){
            hexPoints.append(QPointF(pointy_hex_corner_x(x_pixel,hexSize,i),
                                    pointy_hex_corner_y(y_pixel,hexSize,i)));
        }

        auto* hexagon = new QGraphicsPolygonItem(hexPoints);
        hexGraphicsVector_.push_back(hexagon);
        if(boardScene_ != nullptr){
            boardScene_->addItem(hexagon);
        }
    }

    changeGraphics(newHex);
}


void GameBoard::changeGraphics(const std::shared_ptr<Common::Hex>& hex)
{
    std::string type = hex->getPieceType();
    auto* brush =new QBrush;
    brush->setStyle(Qt::SolidPattern);
    unsigned int i;

    for(i=0; i < hexVector_.size();++i){
        if(hexVector_.at(i) == hex){
            break;
        }
    }

    QGraphicsPolygonItem* hexGraphics = hexGraphicsVector_.at(i);

    //Sets correct colour for hex
    if(type == "Beach"){
        brush->setColor(Qt::yellow);
    }

    else if(type == "Forest"){
        brush->setColor(Qt::green);
    }

    else if(type == "Mountain"){
        brush->setColor(Qt::gray);
    }

    else if(type == "Peak"){
        brush->setColor(Qt::darkGray);
    }

    else if(type == "Coral"){
        brush->setColor(Qt::magenta);
    }

    else{
        brush->setColor(Qt::blue);
    }

    hexGraphics->setBrush(*brush);
}


void GameBoard::makeHexSelected(Common::CubeCoordinate cubeCoord)
{
    if(lastHexSelected_ != nullptr){
        changeGraphics(lastHexSelected_);
    }

    auto* brush =new QBrush;
    brush->setStyle(Qt::SolidPattern);
    brush->setColor(Qt::red);

    for(unsigned int i = 0; i < hexVector_.size(); ++i){
        if(hexVector_.at(i) == getHex(cubeCoord)){
            hexGraphicsVector_.at(i)->setBrush(*brush);
            lastHexSelected_ = getHex(cubeCoord);
            break;
        }
    }
}


std::vector<std::shared_ptr<Common::Pawn>> GameBoard::getPlayersPawnsInHex(
        Common::CubeCoordinate cubeCoord, int player)
{
    std::vector<std::shared_ptr<Common::Pawn>> pawns;
    std::vector<std::shared_ptr<Common::Pawn>> pawnsInHex =
            getHex(cubeCoord)->getPawns();
    for(const auto& pawn : pawnsInHex){
        if(pawn->getPlayerId() == player){
            pawns.push_back(pawn);
        }
    }

    return pawns;
}


int GameBoard::amountOfPlayerOwnedPawns(int player){
    int pawnAmount = 0;

    for(const auto& hex: hexVector_){
        for(const auto& pawn : hex->getPawns()){
            if(pawn->getPlayerId() == player){
                pawnAmount++;
            }
        }
    }

    return pawnAmount;
}


void GameBoard::addTransport(std::shared_ptr<Common::Transport> transport,
                             Common::CubeCoordinate coord)
{
    transport->addHex(getHex(coord));
    transportMap_[transport->getId()] = transport;

    //Add graphics
    if(boardScene_ != nullptr){
        transportGraphicsMap_[transport->getId()] = iconMaker_->
                makeActorIcon(transport->getTransportType());

        transportGraphicsProxyMap_[transport->getId()] = boardScene_->
                addWidget(transportGraphicsMap_.at(transport->getId()));

        setActorOrTransportGraphicsPosition(coord);
    }
}


void GameBoard::moveTransport(int id, Common::CubeCoordinate coord)
{
    if(getHex(coord) != nullptr){
        transportMap_.at(id)->getHex()->removeTransport(transportMap_.at(id));
        transportMap_.at(id)->move(getHex(coord));

        //change graphics
        if(boardScene_ != nullptr){
            setActorOrTransportGraphicsPosition(coord);
        }
    }
}


void GameBoard::removeTransport(int id)
{
    for(auto transport : transportMap_){
        if(transport.second->getId() == id){
            getHex(transport.second->getHex()->getCoordinates())->
                    removeTransport(transport.second);

            transportMap_.erase(transport.first);
            break;
        }
    }
}


void GameBoard::addActor(std::shared_ptr<Common::Actor> actor,
                         Common::CubeCoordinate actorCoord)
{
    if(actor != nullptr && getHex(actorCoord) != nullptr){
        actor->addHex(getHex(actorCoord));
        actorMap_[actor->getId()] = actor;

        //Add graphics
        if(boardScene_ != nullptr){
            actorGraphicsMap_[actor->getId()] = iconMaker_->
                    makeActorIcon(actor->getActorType());

            actorGraphicsProxyMap_[actor->getId()] = boardScene_->
                    addWidget(actorGraphicsMap_.at(actor->getId()));

            setActorOrTransportGraphicsPosition(actorCoord);
        }
    }
}



void GameBoard::setPawnGraphicsPosition(Common::CubeCoordinate coord)
{
    std::vector<std::shared_ptr<Common::Pawn>> pawns = getHex(coord)->getPawns();
    int sceneSizeXmiddle = 550;
    int sceneSizeYmiddle = 500;

    for(unsigned int i = 0; i < pawns.size(); ++i){
        int x_pixel = sceneSizeXmiddle + (52 *coord.z) + (26 * coord.y)
                + (78*coord.x);
        int y_pixel = sceneSizeYmiddle + (45 * -coord.y)+ (45* -coord.x);

        if(i == 0){
            x_pixel -= 20;
            y_pixel -= 17;
        }

        else if(i == 1){
            x_pixel += 5;
            y_pixel -= 17;
        }

        else{
            x_pixel -= 20;
            y_pixel += 2;
        }

        pawnGraphicsMap_.at(pawns.at(i)->getId()) ->setPos(x_pixel,y_pixel);
    }
}



void GameBoard::setActorOrTransportGraphicsPosition(Common::CubeCoordinate coord)
{
    std::vector<std::shared_ptr<Common::Actor>> actors = getHex(coord)->
            getActors();
    std::vector<std::shared_ptr<Common::Transport>> transports = getHex(coord)->
            getTransports();

    int sceneSizeXmiddle = 550;
    int sceneSizeYmiddle = 500;

    int x_pixel = sceneSizeXmiddle + (52 *coord.z) + (26 * coord.y)
            + (78*coord.x);
    int y_pixel = sceneSizeYmiddle + (45 * -coord.y)+ (45* -coord.x);
    int i = 0;

    //Set transport graphics position
    for(const auto& transport : transports){
        transportGraphicsMap_.at(transport->getId())->
                move(x_pixel + 7 * i,y_pixel);
        ++i;
    }

    //set actor graphics position
    for(const auto& actor : actors){
        actorGraphicsMap_.at(actor->getId())->move(x_pixel + 7 * i,y_pixel);
        ++i;
    }
}



void GameBoard::clearGraphics(Common::CubeCoordinate hexClicked,
                              const std::string& actorType)
{
    if(actorType == "shark"){
        clearPawnGraphics(hexClicked);
    }

    else if(actorType == "vortex"){
        clearActorGraphics(hexClicked);
        clearPawnGraphics(hexClicked);
        clearTransportGraphics(hexClicked);

        for(auto hexCoord : getHex(hexClicked)->getNeighbourVector()){
            clearActorGraphics(hexCoord);
            clearPawnGraphics(hexCoord);
            clearTransportGraphics(hexCoord);
        }
    }

    else if(actorType == "seamunster"){
        clearPawnGraphics(hexClicked);
        clearTransportGraphics(hexClicked);
    }

    else if(actorType == "kraken"){
        clearTransportGraphics(hexClicked);
    }

    else{
        std::cout << "Non-existient actor type" << std::endl;
    }
}



void GameBoard::addBoardScene(myGraphicsScene *boardScene)
{
    boardScene_ = boardScene;
}



std::vector<std::shared_ptr<Common::Actor>> GameBoard::actorsOfType(
        const std::string& type)
{

    std::vector<std::shared_ptr<Common::Actor>> actors;
    for(auto actor : actorMap_){
        if(actor.second->getActorType() == type){
            actors.push_back(actor.second);
        }
    }

    return actors;
}



std::vector<std::shared_ptr<Common::Transport> > GameBoard::transportsOfType(
        const std::string& type)
{
    std::vector<std::shared_ptr<Common::Transport>> transports;
    for(auto transport : transportMap_){
        if(transport.second->getTransportType() == type){
            transports.push_back(transport.second);
        }
    }

    return transports;
}


std::pair<int, int> GameBoard::checkGoals(Common::CubeCoordinate coord)
{

    std::pair<int, int> points = {-1,-1};
    int pawnId = -1;

    for(const auto& hex : hexVector_){
        if(hex->getPieceType() == "Coral"){
            for(auto pawn : pawnMap_){
                //If pawn is on coral give points
                if(pawn.second->getCoordinates() == hex->getCoordinates()){
                    points.first = pawn.second->getPlayerId();
                    points.second = 100;
                    pawnId = pawn.first;
                    coord = hex->getCoordinates();
                }
            }
        }
    }

    //Remove pawn
    if(pawnId != -1){
        removePawn(pawnId);
        clearPawnGraphics(coord);
    }

    return points;
}



int GameBoard::pointy_hex_corner_x(int center,int  size,int i){
    int angle_deg = (60 * i) - 30;
    double angle_rad = (M_PI / 180) * angle_deg;
    return center + size * cos(angle_rad);
}



int GameBoard::pointy_hex_corner_y(int center,int  size,int i){
    int angle_deg = (60 * i) - 30;
    double angle_rad = (M_PI / 180) * angle_deg;
    return center + size * sin(angle_rad);
}



void GameBoard::clearPawnGraphics(Common::CubeCoordinate coord)
{
    for(auto pawn : pawnMap_){
        if(pawn.second->getCoordinates() == coord){
            removePawn(pawn.first);
            boardScene_->removeItem(pawnGraphicsMap_.at(pawn.first));
            pawnMap_.erase(pawn.first);
        }
    }
}



void GameBoard::clearActorGraphics(Common::CubeCoordinate coord)
{
    for(auto actor : actorMap_){
        if(actor.second->getHex()->getCoordinates() == coord){
            removeActor(actor.second->getId());
            boardScene_->removeItem(actorGraphicsProxyMap_.at(actor.second->
                                                              getId()));
            actorMap_.erase(actor.first);
            break;
        }
    }
}



void GameBoard::clearTransportGraphics(Common::CubeCoordinate coord)
{
    for(auto transport : transportMap_){
        if(transport.second->getHex()->getCoordinates() == coord){
            removeTransport(transport.second->getId());
            boardScene_->removeItem(transportGraphicsProxyMap_
                                    .at(transport.second->getId()));
            transportMap_.erase(transport.first);
            break;
        }
    }
}

}
