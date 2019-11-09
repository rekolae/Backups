#include <QString>
#include <QtTest>
#include "gamestate.hh"

class GameStateTest : public QObject
{
    Q_OBJECT

public:
    GameStateTest();

private Q_SLOTS:
    void testSetCurrentGamePhase();
    void testSetCurrentPlayer();
    void testChangePlayer();
    void testChangeGameState();

private:
    std::shared_ptr<Student::GameState> state_
    = std::make_shared<Student::GameState>();
};


GameStateTest::GameStateTest()
{

}



void GameStateTest::testSetCurrentGamePhase()
{
    state_->changeGamePhase(Common::MOVEMENT);
    QVERIFY(state_->currentGamePhase() == Common::MOVEMENT);
}

void GameStateTest::testSetCurrentPlayer()
{
    state_->changePlayerTurn(0);
    QVERIFY(state_->currentPlayer() == 0);
}

void GameStateTest::testChangePlayer()
{
    QVERIFY(state_->currentPlayer() == 0);
    state_->changePlayerTurn(2);
    QVERIFY(state_->currentPlayer() == 2);

}

void GameStateTest::testChangeGameState()
{
    QVERIFY(state_->currentGamePhase() == Common::MOVEMENT);
    state_->changeGamePhase(Common::SINKING);
    QVERIFY(state_->currentGamePhase() == Common::SINKING);

}

QTEST_APPLESS_MAIN(GameStateTest)

#include "tst_gamestatetest.moc"
