#include "BatteryDecorator.h"
#include "SpinDecorator.h"
#include "Beeline.h"
#include "AstarStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "HubFactory.h"

#include <iostream>
#include <string>
#include <vector>
#include "math/vector3.h"
#include <cmath>

BatteryDecorator::BatteryDecorator(IStrategy *strategy_) : DroneDecorator(strategy_) {
    strategy = strategy_;

    // Generate all 6 hubs
    HubFactory* hf = new HubFactory();
    Hub* hub1 = hf->CreateEntity(Vector3(167, 197, 250));
    Hub* hub2 = hf->CreateEntity(Vector3(500, 197, 250));
    Hub* hub3 = hf->CreateEntity(Vector3(833, 197, 250));
    Hub* hub4 = hf->CreateEntity(Vector3(167, 394, 250));
    Hub* hub5 = hf->CreateEntity(Vector3(500, 394, 250));
    Hub* hub6 = hf->CreateEntity(Vector3(833, 394, 250));
    hubs.push_back(hub1);
    hubs.push_back(hub2);
    hubs.push_back(hub3);
    hubs.push_back(hub4);
    hubs.push_back(hub5);
    hubs.push_back(hub6);
}

bool BatteryDecorator::IsCompleted(){
    return strategy->IsCompleted();
}

double BatteryDecorator::ComputeDrain(IEntity* entity, double dt) {
    Beeline* beeline = dynamic_cast<Beeline*>(strategy);
    if (beeline) {
        Vector3 start = beeline->GetPos();
        Vector3 des = beeline->GetDes();
        return (2.0 * (start.Distance(des) / entity->GetSpeed())) / 7;
    }

    SpinDecorator* spin = dynamic_cast<SpinDecorator*>(strategy);
    if (spin) {
        AstarStrategy* astar = dynamic_cast<AstarStrategy*>(spin->GetStrategy());
        if (astar) {
            std::vector<std::vector<float>> path = astar->GetPath();
            return path.size() / 7;
        }
        DfsStrategy* dfs = dynamic_cast<DfsStrategy*>(spin->GetStrategy());
        if (dfs) {
            std::vector<std::vector<float>> path = dfs->GetPath();
            return path.size() / 7;
        }
        DijkstraStrategy* dijk = dynamic_cast<DijkstraStrategy*>(spin->GetStrategy());
        if (dijk) {
            std::vector<std::vector<float>> path = dijk->GetPath();
            return path.size() / 7;
        }
    }
}

IStrategy* BatteryDecorator::closestHub(IEntity* entity) {
    double min = 1000000;
    Hub* minHub = NULL;
    for(int i = 0; i < hubs.size(); i++) {
        Vector3 HubPos = hubs.at(i)->GetPosition();
        Vector3 DronePos = entity->GetPosition();
        double distance = DronePos.Distance(HubPos);
        if(distance < min){
            min = distance;
            minHub = hubs.at(i);
        }
    }
    return new Beeline(entity->GetPosition(), minHub->GetPosition());
}

void BatteryDecorator::Charge() {
    if ((percentage + 0.1) > 100) {
        percentage = 100;
    }
    else {
        percentage = percentage + 0.1;
    }
    if ((std::fmod(percentage, 10) <= 0.1)) {
        std::cout << "Charging: " << percentage << "%" << std::endl;
    }
}

double BatteryDecorator::GetPercentage() {
    return percentage;
}

bool BatteryDecorator::GetToHub() {
    return toHub;
}

bool BatteryDecorator::GetCharging() {
    return charging;
}

void BatteryDecorator::SetToHub(bool b) {
    toHub = b;
}

void BatteryDecorator::Move(IEntity* entity, double dt) {
    if (!charging && !flag) {
        if (counter == 0) {
            double drain = ComputeDrain(entity, dt);
            percentage = percentage - drain;
            std::cout << percentage << "%" << std::endl;
        }
        counter++;
        strategy->Move(entity, dt);
    }
    if (flag && !toHub) {
        toHubStrategy = closestHub(entity);
        toHub = true;
        toHubStrategy->Move(entity, dt);
    }
    if (toHub) {
        if (counter2 == 0) {
            double drain2 = ComputeDrain(entity, dt);
            percentage = percentage - drain2;
            std::cout << "Moving to charging hub" << std::endl;
            std::cout << percentage << "%" << std::endl;
        }
        counter2++;
        toHubStrategy->Move(entity, dt);
        if(toHubStrategy->IsCompleted()){
            toHub = false;
            flag = false;
            charging = true;
        }
    }
    if(charging){
        if(percentage < 100){
            Charge();
        }
        if(percentage >= 100) {
            charging = false;
        }
    }
    // if (percentage > 35 && !charging && !toHub) {
    //     if (counter == 0) {
    //         double drain = ComputeDrain(entity, dt);
    //         percentage = percentage - drain;
    //         std::cout << percentage << std::endl;
    //     }
    //     counter++;
    //     strategy->Move(entity, dt);
    // }
    // else {
    //     if (!toHub) {
    //         toHubStrategy = closestHub(entity);
    //         toHub = true;
    //         flag = true;
    //         toHubStrategy->Move(entity, dt);
    //     }
    //     if(toHub && !charging){
    //         if (counter2 == 0) {
    //             double drain2 = ComputeDrain(entity, dt);
    //             percentage = percentage - drain2;
    //             std::cout << percentage << std::endl;
    //         }
    //         counter2++;
    //         toHubStrategy->Move(entity, dt);
    //         if(toHubStrategy->IsCompleted()){
    //             toHub = false;
    //             charging = true;
    //         }
    //     }
    //     if(charging){
    //         if(percentage < 100){
    //             Charge();
    //         }
    //         if(percentage >= 100) {
    //             charging = false;
    //             flag = false;
    //         }
    //     }
    // }
}