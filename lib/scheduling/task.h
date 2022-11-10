#ifndef __TASK_H_INCLUDED
#define __TASK_H_INCLUDED

#include "lib.h"

namespace Scheduling {
    class Task {
    public:
        virtual bool isEnabled() const;
        void disable();
        void enable();

        virtual void init() = 0;
        virtual void tick() = 0;
    protected:
        bool is_enabled;
    };

    class PeriodicTask : public Task {
    public:
        virtual void init() = 0;
        virtual void tick() = 0;
    protected:
        bool canRun();

        timestamp_t last_execution;
        timestamp_t period;
    };
}

#endif