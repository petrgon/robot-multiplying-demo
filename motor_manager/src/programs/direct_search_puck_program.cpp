#include "../../include/programs/direct_search_puck_program.h"

DirectSearchPuckProgram::DirectSearchPuckProgram(int irFrequency) : Program(), irFrequency(irFrequency)
{
    State *searchLeft = new SearchLeftState(this, SEARCHING_TIME);
    State *turnRight = new SearchRightState(this, CURVE_TIME);
    State *moveForward = new MoveForwardState(this, MOVE_FORWARD_TIME);
    State *catchLight = new MoveForwardState(this);
    State *leftCurve = new MoveState(this, CURVE_LEFT_SPEED, CURVE_RIGHT_SPEED, COLLISION_TIME);
    State *endProgram = new ProgramTimeoutState(this);
    State *moveBack = new MoveBackwardState(this, COLLISION_TIME);
    State *unexpectedCollision = new MoveBackwardState(this, COLLISION_TIME);

    moveForward->setCollisionNextState(moveBack)->setLightDetectedNextState(catchLight);
    moveForward->setTimeElapsedNextState(searchLeft);

    moveBack->setTimeElapsedNextState(leftCurve);

    leftCurve->setTimeElapsedNextState(turnRight)->setLightDetectedNextState(catchLight);
    leftCurve->setCollisionNextState(unexpectedCollision);

    catchLight->setLightLostNextState(turnRight);

    turnRight->setLightDetectedNextState(catchLight)->setTimeElapsedNextState(searchLeft);
    turnRight->setCollisionNextState(unexpectedCollision);

    searchLeft->setLightDetectedNextState(catchLight)->setCollisionNextState(unexpectedCollision);
    searchLeft->setTimeElapsedNextState(endProgram);

    stateConut = 8;
    allStates = new State *[stateConut];
    allStates[0] = searchLeft;
    allStates[1] = turnRight;
    allStates[2] = moveForward;
    allStates[3] = catchLight;
    allStates[4] = leftCurve;
    allStates[5] = endProgram;
    allStates[6] = moveBack;
    allStates[7] = unexpectedCollision;

    actualState = nullptr;
    nextState = moveForward;

    SensorManager::getInstance()->subscribePuckAquiredEvent(this);
}

DirectSearchPuckProgram::~DirectSearchPuckProgram()
{
    SensorManager::getInstance()->unsubscribeFromAll(this);
}

void DirectSearchPuckProgram::puckAquiredEventHandler()
{
    ProgramManager::getInstance()->setProgram(new ScoreProgram(irFrequency));
}

void DirectSearchPuckProgram::timeElapsedEventHandler()
{
    ProgramManager::getInstance()->setProgram(new CatchPuckProgram(irFrequency));
}