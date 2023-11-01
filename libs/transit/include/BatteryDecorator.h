#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H_

#include <vector>
#include "DroneDecorator.h"
#include "hub.h"

#include "IStrategy.h"

class BatteryDecorator: public DroneDecorator {
    public:
        BatteryDecorator(IStrategy *strategy_);
        bool IsCompleted();
        double ComputeDrain(IEntity* entity, double dt);
        void Charge();
        IStrategy* closestHub(IEntity* entity);
        double GetPercentage();
        bool GetToHub();
        bool GetCharging();
        void SetToHub(bool b);
        void SetFlag(bool f) {flag = f;}
        bool GetFlag() {return flag;}
        void Move(IEntity* entity, double dt);
    protected:
        IStrategy* toHubStrategy;
        std::vector<Hub*> hubs;
        bool charging = false;
        bool toHub = false;
        bool flag = false;
};

#endif