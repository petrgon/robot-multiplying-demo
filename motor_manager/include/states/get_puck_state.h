#ifndef GET_PUCK_STATE_MANAGER_H
#define GET_PUCK_STATE_MANAGER_H

#include "state.h"
#include "../managers/motor_manager.h"
#include "../managers/sensor_manager.h"
#include "../managers/callback_time_manager.h"
#include <vector>
#include <atomic>

class GetPuckState : public State
{
public:
  GetPuckState();
  ~GetPuckState() override;

  void run() override;

  void timeElapsedEventHandler() override;

  void puckAquiredEventHandler() override;
  void puckLostEventHandler() override;

  void lightDetectedEventHandler() override;
  void lightLostEventHandler() override;

  void leftTouchTriggeredEventHandler() override;
  void leftTouchFreedEventHandler() override;

  void rightTouchTriggeredEventHandler() override;
  void rightTouchFreedEventHandler() override;

  void bothTouchTriggeredEventHandler() override;
  void bothTouchFreedEventHandler() override;

private:
  enum Actions {
    SEARCH_LEFT, SEARCH_RIGHT, MOVE_FORWARD, PUCK_TRIGGERED, 
    LEFT_TRIGGERED, RIGHT_TRIGGERED, BOTH_TRIGGERED, LIGHT_DETECTED
  };

  std::atomic<bool> timeIsUp;
  bool puckTouchTriggered;
  bool lightDetected;
  bool leftTouchTriggered;
  bool rightTouchTriggered;

  Actions actualAction;
};
#endif /*GET_PUCK_STATE_MANAGER_H*/
