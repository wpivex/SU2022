#include "vex.h"
#include <type_traits>

// Velocity from -1 to 1
void setMotorVelocity(vex::motor m, vex::directionType d, double percent) {
    if (percent < 0) {
        d = (d == vex::forward) ? vex::reverse : vex::forward;
        percent = -percent;
    }

    percent = fmin(1, fmax(-1, percent)); // bound between -1 and 1

    m.spin(d, percent * 12.0, vex::voltageUnits::volt);
}

template <class F>
vex::task launch_task(F&& function) {
  //static_assert(std::is_invocable_r_v<void, F>);
  return vex::task([](void* parameters) {
    std::unique_ptr<std::function<void()>> ptr{static_cast<std::function<void()>*>(parameters)};
    (*ptr)();
    return 0;
  }, new std::function<void()>(std::forward<F>(function)));
}