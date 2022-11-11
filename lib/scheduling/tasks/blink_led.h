#include "task.h"
#include "led.h"

namespace Tasks {
    
    class BlinkLed : public Scheduling::PeriodicTask {
    public:
        BlinkLed() = default;
        BlinkLed(Components::Led led, timestamp_t period);

        void init();
        void tick();
    private:
        Components::Led led;
    };
}