#include "DroneDecorator.h"

bool DroneDecorator::IsCompleted(){
    return strategy->IsCompleted();
}

void DroneDecorator::Move(IEntity* entity, double dt){
    strategy->Move(entity, dt);
}

double DroneDecorator::percentage = 100;