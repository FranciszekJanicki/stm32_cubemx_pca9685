#ifndef SFO_HPP
#define SFO_HPP

#include "matrix.hpp"

namespace Utility {

    template <typename T, std::size_t nX, std::size_t nY = 1UL, std::size_t nU = nY>
    struct SFO {
    public:
        template <std::size_t N, std::size_t M>
        using Mtx = Matrix<T, N, M>;

        Mtx<nX, 1UL>
        get_estimated_state(this SFO& self, Mtx<nU, 1UL> const& u, Mtx<nY, 1UL> const& y)
        {
            try {
                self.predict(u, y);
                self.correct(u, y);
                return self.x;
            } catch (std::runtime_error const& error) {
                throw error;
            }
        }

        Mtx<nX, 1UL> operator()(this SFO& self, Mtx<nU, 1UL> const& u, Mtx<nY, 1UL> const& y)
        {
            try {
                return self.get_estimated_state(u, y);
            } catch (std::runtime_error const& error) {
                throw error;
            }
        }

        void predict(this SFO& self, Mtx<nU, 1UL> const& u, Mtx<nY, 1UL> const& y)
        {
            try {
                auto const x_hat = self.A * self.x + self.B * u;
                self.x = x_hat;
            } catch (std::runtime_error const& error) {
                throw error;
            }
        }

        void update(this SFO& self, Mtx<nU, 1UL> const& u, Mtx<nY, 1UL> const& y)
        {
            try {
                auto const y_hat = self.C * self.x + self.D * u;
                auto const x = self.x + self.K * (y - y_hat);
                self.x = x;
            } catch (std::runtime_error const& error) {
                throw error;
            }
        }

        /* state */
        Mtx<nX, 1UL> x = Mtx<nX, 1UL>{};

        /* state model */
        Mtx<nX, nX> A = Mtx<nX, nX>{};
        Mtx<nX, nU> B = Mtx<nX, nU>{};
        Mtx<nY, nX> C = Mtx<nY, nX>{};
        Mtx<1UL, nU> D = Mtx<1UL, nU>{};

        /* state gain */
        Mtx<nU, nX> K = Mtx<nU, nX>{};
    };

}; // namespace Utility

#endif // SFO_HPP