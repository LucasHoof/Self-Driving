#include "HubFactory.h"

Hub* HubFactory::CreateEntity(Vector3 pos_) {
    // std::cout << "Hub Created at (" << pos_[0] << ", " << pos_[1] << ", " << pos_[2] << ")" << std::endl;
    return new Hub(pos_);
}