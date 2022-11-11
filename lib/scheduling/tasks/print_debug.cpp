#include <utils.h>
#include "print_debug.h"


namespace Tasks {
    template<typename T>
    PrintDebug<T>::PrintDebug(timestamp_t period) {
        setPeriodAndRestartTimer(period);
    }

    template<typename T>
    void PrintDebug<T>::init() {}

    template<typename T>
    void PrintDebug<T>::tick() {
        if (!canRun()) {
            return;
        }

        for (int i=0; i<last_idx; i++) {
            String msg = "Component " + Strign(i) + " has value " + String(components[i]->read());

            Logger::Logger::getInstance()
                .log(Logger::LogLevel::Debug, msg.c_str())
        }
        markExecutedNow();
    }

    template<typename T>
    void PrintDebug<T>::addComponent(Components::ReadableComponent<T>* component) {
        if (last_idx == MAX_NUMBER_OF_COMPONENTS) {
            return;
        }

        components[last_idx] = component;
        last_idx++;
    }

}