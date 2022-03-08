#pragma once
#include "WhenYouWishUponAStar/Component.h"

namespace WhenYouWishUponAStar {

    class Starchaser :
        public ComponentBase
    {
    public:
        Starchaser(GameObject* _parent, const ComponentFamilyId _id);
        ~Starchaser();
    };
}
