#ifndef DRONE_DECORATOR_H_
#define DRONE_DECORATOR_H_

#include <vector>
#include "IStrategy.h"

class DroneDecorator: public IStrategy {
public:
    DroneDecorator(IStrategy *strategy_) {strategy = strategy_; counter = 0; counter2 = 0;}
    void Move(IEntity* entity, double dt);
    bool IsCompleted();

protected:
    IStrategy* strategy;
    static double percentage;
    int counter;
    int counter2;
};

#endif