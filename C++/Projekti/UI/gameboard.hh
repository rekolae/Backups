#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include "igameboard.hh"
#include "pawn.hh"
#include "iconmaker.hh"
#include "mygraphicsscene.hh"
#include "hex.hh"
#include "actor.hh"
#include "transport.hh"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QGraphicsProxyWidget>
#include <map>
#include <unordered_map>


namespace Student{

class GameBoard : public Common::IGameBoard
{
public:

    /**
     * @brief GameBoard Constructor.
     */
    GameBoard();
    ~GameBoard();

    /**
     * @brief checkTileOccupation Checks the current amount of pawns on the tile
     * @param tileCoord The location of the tile in coordinates.
     * @return The number of the pawns in the tile or -1 if the tile does not exist.
     * @post Exception quarantee: strong
     */
    int checkTileOccupation(Common::CubeCoordinate tileCoord) const;


    /**
     * @brief isWaterTile checks if the tile is a water tile.
     * @param tileCoord The location of the tile in coordinates.
     * @return true, if the tile is a water tile, else (or if the tile does not exist) false.
     * @post Exception quarantee: nothrow
     */
    bool isWaterTile(Common::CubeCoordinate tileCoord) const;


    /**
     * @brief getHex returns the hex gameboard tile
     * @param hexCoord The location of the hex in coordinates.
     * @return Shared pointer to the hex or nullptr, if the hex not exists.
     * @post Exception quarantee: nothrow
     */
    std::shared_ptr<Common::Hex> getHex(Common::CubeCoordinate hexCoord) const;


    /**
     * @brief addPawn adds a new pawn to the game
     * @param playerId. Id of player, whose pawn is added
     * @param pawnId. Id of the pawn
     * @post Pawn is added to the game. Exception quarantee: basic
     */
    void addPawn(int playerId, int pawnId);


    /**
     * @brief addPawn adds a new pawn to the game
     * @param playerId. Id of player, whose pawn is added
     * @param pawnId. Id of the pawn
     * @param coord. CubeCoordinate, where pawn is added
     * @post Pawn is added to the game. Exception quarantee: basic
     */
    void addPawn(int playerId, int pawnId, Common::CubeCoordinate coord);


    /**
     * @brief movePawn sets a new location for the pawn.
     * @details Pawn is added to a Hex that is in the specified coordinates and removed from the old.
     * If there is no Hex-object in specified coordinates, the pawn remains in the old Hex.
     * @param pawnId The identifier of the pawn.
     * @param pawnCoord The target location of the pawn in coordinates.
     * @pre Pawn exists
     * @post Pawn is moved to the target location or stays in place if location doesn't exist.
     * Exception quarantee: basic
     */
    void movePawn(int pawnId, Common::CubeCoordinate pawnCoord);


    /**
     * @brief removePawn removes a pawn.
     * @details Removed pawn should be removed from a Hex-object if it is contained in one.
     * @param pawnId The identifier of the pawn.
     * @pre Pawn exists
     * @post pawn matching the id is removed. Exception quarantee: basic
     */
    void removePawn(int pawnId);


    /**
     * @brief moveActor sets a new location for the actor.
     * @details Actor is added to a Hex that is in the specified coordinates and removed from the old.
     * If there is no Hex-object in specified coordinates, the actor remains in the old Hex.
     * @param actorId The identifier of the actor.
     * @param actorCoord The target location of the actor in coordinates.
     * @pre Actor exists
     * @post actor actorId is moved to a new location or stays in place if location doesn't exist.
     * Exception quarantee: basic
     */
    void moveActor(int actorId, Common::CubeCoordinate actorCoord);


    /**
     * @brief removeActor removes an actor.
     * @details The actor should be removed from a Hex-object.
     * @param actorId The identifier of the actor.
     * @pre Actor exists
     * @post Actor actorId is removed. Exception quarantee: basic
     */
    void removeActor(int actorId);


    /**
     * @brief addHex adds a new hex tile to the board
     * @param newHex Pointer of a new hex to add
     * @pre newHex is valid
     * @post newHex is added to the board. Any existing hex at the same
     * coordinates is replaced. Exception quarantee: basic
     */
    void addHex(std::shared_ptr<Common::Hex> newHex);


    /**
     * @brief changeGraphics gets correct grphics for hex
     * @param hex Pointer of hex
     */
    void changeGraphics(const std::shared_ptr<Common::Hex>& hex);


    /**
     * @brief makeHexSelected Changes hexes graphics to make it selected(red)
     * @param cubeCoord Coordinates of the hex
     */
    void makeHexSelected(Common::CubeCoordinate cubeCoord);


    /**
     * @brief getPawn Return pawn with specific id
     * @param pawnId Id of the pawn
     * @return pointer to pawn
     */
    Common::Pawn getPawn(int pawnId);


    /**
     * @brief getPlayersPawnsInHex Gives players pawns in a hex
     * @param cubeCoord coordinate of the hex
     * @param player Id of player
     * @return players pawns in a vector
     */
    std::vector<std::shared_ptr<Common::Pawn>>
        getPlayersPawnsInHex(Common::CubeCoordinate cubeCoord, int player);


    /**
     * @brief amountOfPlayerOwnedPawns tells players pawn amount
     * @param player. Id of player
     * @return Players pawn amount
     */
    int amountOfPlayerOwnedPawns(int player);


    /**
     * @brief addTransport adds a new transport to the game board
     * @param transport transport to be added
     * @param coord
     * @pre coordinates must contain a hex
     * @post Transport has been added to the hex in target coordinates
     */
    void addTransport(std::shared_ptr<Common::Transport> transport,
                      Common::CubeCoordinate coord);


    /**
     * @brief moveTransport sets a new location for the transport.
     * @param id The identifier of the transport.
     * @param coord The target location of the transport in coordinates.
     * @post transport is moved to a new location: Exception quarantee: basic
     */
    void moveTransport(int id, Common::CubeCoordinate coord);


    /**
     * @brief removeTransport removes an transport.
     * @param id The identifier of the transport.
     * @post transport removed from the gameboard. Exception quarantee: basic
     */
    void removeTransport(int id);


    /**
     * @brief addActor adds a actor to the game board
     * @param actor
     * @param actorCoord
     * @pre CubeCoordinate must contain a Hex-tile. Actor is not null-pointer.
     * @post actor has been added to the hex in target coordinates
     */
    void addActor(std::shared_ptr<Common::Actor> actor,
                  Common::CubeCoordinate actorCoord);


    /**
     * @brief setPawnGraphicsPosition Calculates and sets correct position for pawn graphics in a hex
     * @param coord Coordinates of the hex
     */
    void setPawnGraphicsPosition(Common::CubeCoordinate coord);


    /**
     * @brief setActorOrTransportGraphicsPosition Calculates and sets correct position for
     * actor/transport graphics in a hex
     * @param coord Coordinates of the hex
     */
    void setActorOrTransportGraphicsPosition(Common::CubeCoordinate coord);


    /**
     * @brief clearGraphics Removes correct graphics from hex according to actor type
     * @param hexClicked Coordinats of the hex
     * @param actorType Type of the actor
     */
    void clearGraphics(Common::CubeCoordinate hexClicked,
                       const std::string& actorType);


    /**
     * @brief addBoardScene Adds board scene
     * @param boardScene shared pointer to board scene
     */
    void addBoardScene(myGraphicsScene* boardScene);


    /**
     * @brief actorsOfType Gives all actors of given type
     * @param type type of the actor
     * @return shared pointer vector of actors
     */
    std::vector<std::shared_ptr<Common::Actor> >
        actorsOfType(const std::string& type);


    /**
     * @brief transportsOfType Gives all transports of given type
     * @param type type of the transport
     * @return shared pointer vector of transports
     */
    std::vector<std::shared_ptr<Common::Transport>>
        transportsOfType(const std::string& type);


    /**
     * @brief checkGoals Checks if pawn has entered a coral tile and gives points
     * @param coord Coordinates of the hex
     * @return pair with player id and ammount of points
     */
    std::pair<int,int> checkGoals(Common::CubeCoordinate coord);

private:

    /**
     * @brief pointy_hex_corner_x Calculates a corner for hexagon
     * @param center center coordinates
     * @param size size of hexagon
     * @param i corners number
     * @return Corner coordinate
     */
    int pointy_hex_corner_x(int center,int  size,int i);

    /**
     * @brief pointy_hex_corner_y Calculates a corner for hexagon
     * @param center center coordinates
     * @param size size of hexagon
     * @param i corners number
     * @return Corner coordinate
     */
    int pointy_hex_corner_y(int center,int  size,int i);

    /**
     * @brief changeGraphics Changes graphics acconrding to actors action
     */
    void changeGraphics(QGraphicsPolygonItem*);

    /**
     * @brief clearPawnGraphics Removes pawn graphics
     * @param coord Coordinates of pawn
     */
    void clearPawnGraphics(Common::CubeCoordinate coord);

    /**
     * @brief clearActorGraphics Removes actor graphics from hex
     * @param coord Coordinates of actor
     */
    void clearActorGraphics(Common::CubeCoordinate coord);

    /**
     * @brief clearTransportGraphics Removes transport graphics from hex
     * @param coord Coordinates of hex
     */
    void clearTransportGraphics(Common::CubeCoordinate coord);

    myGraphicsScene* boardScene_ = nullptr;

    std::shared_ptr<Student::IconMaker> iconMaker_ =
            std::make_shared<Student::IconMaker>();

    //Hex containers
    std::vector<std::shared_ptr<Common::Hex>> hexVector_;
    std::vector<QGraphicsPolygonItem*> hexGraphicsVector_;

    //Pawn conatiners
    std::map<int,std::shared_ptr<Common::Pawn>> pawnMap_;
    std::map<int,QGraphicsPolygonItem*> pawnGraphicsMap_;

    //Transport containers
    std::map<int,std::shared_ptr<Common::Transport>> transportMap_;
    std::map<int,QLabel*> transportGraphicsMap_;
    std::map<int,QGraphicsProxyWidget*> transportGraphicsProxyMap_;

    //Actor containers
    std::map<int,std::shared_ptr<Common::Actor>> actorMap_;
    std::map<int,QLabel*> actorGraphicsMap_;
    std::map<int,QGraphicsProxyWidget*> actorGraphicsProxyMap_;

    std::shared_ptr<Common::Hex> lastHexSelected_ = nullptr;

};

};


#endif // GAMEBOARD_HH
