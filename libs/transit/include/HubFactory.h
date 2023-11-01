#ifndef HUB_FACTORY_H_
#define HUB_FACTORY_H_

#include "entity.h"
#include "IEntityFactory.h"
#include "hub.h"

class HubFactory: public IEntityFactory {
    public:
        Hub* CreateEntity(Vector3 pos_);
        IEntity* CreateEntity(JsonObject& entity) {}
};

#endif