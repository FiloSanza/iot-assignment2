#include "logger.h"
#include "print_debug.h"

namespace Tasks {
    template<typename T>
    PrintDebug<T>::PrintDebug(timestamp_t period) : last_idx(0) {
        setPeriodAndRestartTimer(period);
    }

    template<typename T>
    void PrintDebug<T>::init() {}

    template<typename T>
    void PrintDebug<T>::tick() {
        if (!canRun()) {
            return;
        }

        for (uint16_t i=0; i<last_idx; i++) {
            Logger::Message msg;
            msg.setLevel(Logger::LogLevel::Debug)
               .setSource(TaskId::PrintDebug)
               .setData(String(components[i].component->read()))
               .setDescription(components[i].name)
               .log();
        }
        markExecutedNow();
    }

    template<typename T>
    void PrintDebug<T>::addComponent(String name, Components::ReadableComponent<T>* component) {
        if (last_idx == MAX_NUMBER_OF_COMPONENTS) {
            return;
        }

        components[last_idx] = {name, component};
        last_idx++;
    }

    // See: https://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor
    template class PrintDebug<bool>;
    template class PrintDebug<float>;
    template class PrintDebug<uint32_t>;
    template class PrintDebug<ButtonState>;
}