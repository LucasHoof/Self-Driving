#ifndef HUB_H_
#define HUB_H_

#include "util/json.h"
#include "entity.h"
// #include "BatteryDecorator.h"
#include "math/vector3.h"

class Hub: public IEntity {
    public:
        Hub(Vector3 pos_);

        ~Hub() = default;

        Vector3 GetPosition() const { return position; }

        Vector3 GetDirection() const {}

        Vector3 GetDestination() const {}

        JsonObject GetDetails() const {}

        float GetSpeed() const {}

        bool GetAvailability() const {}

        std::string GetStrategyName() const {}

        void SetAvailability(bool choice) {}

        void Update(double dt, std::vector<IEntity*> scheduler) {}

        void SetDirection(Vector3 dir_) {}

        void SetDestination(Vector3 des_) {}

        void SetStrategyName(std::string strategyName_) {}

        void Rotate(double dt) {}

        void SetPosition(Vector3 pos_) { position = pos_; }

    protected:
        Vector3 position;
};

#endif