#include "scheduler.h"

namespace Scheduling {
    Scheduler::Scheduler()
        : last_idx(0) {}

    bool Scheduler::schedule(Task* task) {
        if (last_idx == MAX_NUMBER_OF_TASKS) {
            return false;
        }

        tasks[last_idx] = task;
        last_idx++;
    }

    void Scheduler::tick() {
        for (int i=0; i<last_idx; i++) {
            if (tasks[i]->isEnabled()) {
                tasks[i]->tick();
            }
        }
    }
}