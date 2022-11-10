#include "task.h"

namespace Scheduling {
    bool Task::isEnabled() const {
        return is_enabled;
    }

    void Task::disable() {
        is_enabled = false;
    }

    void Task::enable() {
        is_enabled = true;
    }
 
    bool PeriodicTask::canRun() {
        return is_enabled && (last_execution - millis()) >= period;
    }
}