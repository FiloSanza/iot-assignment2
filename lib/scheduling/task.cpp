#include "task.h"

namespace Scheduling {
    bool Task::isEnabled() const {
        return is_enabled;
    }

    void Task::disable() {
        is_enabled = false;
    }

    void Task::enable() {
        is_enabled = false;
    }

    bool PeriodicTask::canRun() {
        return is_enabled && ((millis() - last_execution) >= period);
    }

    void PeriodicTask::setPeriod(timestamp_t period) {
        period = period;
    }

    void PeriodicTask::markExecutedNow() {
        last_execution = millis();
    }

    void PeriodicTask::setPeriodAndRestartTimer(timestamp_t period) {
        setPeriod(period);
        markExecutedNow();
    }
}