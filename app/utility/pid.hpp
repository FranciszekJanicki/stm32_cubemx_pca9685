#ifndef PID_HPP
#define PID_HPP

#include "utility.hpp"
#include <concepts>
#include <utility>

namespace Utility {

    template <typename T>
    struct PID {
        T operator()(this PID& self, T const e, T const dt) noexcept
        {
            return self.get_sat_u(e, dt);
        }

        T get_sat_u(this PID& self, T const e, T const dt) noexcept
        {
            auto const u = self.get_control(e, dt);
            auto const sat_u = std::clamp(u, -self.sat_u, self.sat_u);

            self.prev_sat_e = std::exchange(self.sat_e, u - sat_u);
            self.prev_e = e;

            return sat_u;
        }

        T get_u(this PID& self, T const e, T const dt) noexcept
        {
            return self.get_p(e) + self.get_i(e, dt) + self.get_d(e, dt);
        }

        T get_p(this PID& self, T const e) noexcept
        {
            return self.kP * e;
        }

        T get_d(this PID& self, T const e, T const dt) noexcept
        {
            self.dot_e = Utility::differentiate(e, self.prev_e, dt, self.dot_e, self.tD);

            return self.kD * self.dot_e;
        }

        T get_integral(this PID& self, T const e, T const dt) noexcept
        {
            self.int_e += Utility::integrate(e, self.prev_e, dt);
            self.sat_int_e += Utility::integrate(self.sat_e, self.prev_sat_e, dt);

            return self.kI * self.int_e - self.control_gain * self.sat_int_e;
        }

        // basic PID parameters
        T kP{};
        T kI{};
        T kD{};
        T tD{};

        // anti windup parameters
        T kC{};
        T sat{};

        // basic PID internal state
        T prev_e{};
        T int_e{};
        T dot_e{};

        // anti windup internal state
        T sat_e{};
        T prev_sat_e{};
        T int_sat_e{};
    };

}; // namespace Utility

#endif // PID_HPP
