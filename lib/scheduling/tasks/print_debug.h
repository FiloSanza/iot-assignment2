#ifndef _PRINT_DEBUG_INCLUDED
#define _PRINT_DEBUG_INCLUDED

#include "task.h"
#include "consts.h"
#include "types.h"

namespace Tasks {
    template<typename T>
    class PrintDebug : public Scheduling::PeriodicTask {
    public:
        PrintDebug(timestamp_t period);

        void init();
        void tick();
        void addComponent(String name, Components::ReadableComponent<T>* component);

    private:
        struct DebugComponent {
            String name;
            Components::ReadableComponent<T>* component;
        };

        uint16_t last_idx;
        DebugComponent components[MAX_NUMBER_OF_COMPONENTS];
    };
}

#endif