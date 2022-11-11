#ifndef _PRINT_DEBUG_INCLUDED
#define _PRINT_DEBUG_INCLUDED

#include "task.h"
#include "component.h"
#include "consts.h"

namespace Tasks {
    template<typename T>
    class PrintDebug : public Scheduling::PeriodicTask {
    public:
        PrintDebug(timestamp_t period);

        void init();
        void tick();
        void addComponent(Components::ReadableComponent<T>* component);

    private:
        uint16_t last_idx;
        Components::ReadableComponent<T>* components[MAX_NUMBER_OF_COMPONENTS];
    };
}

#endif