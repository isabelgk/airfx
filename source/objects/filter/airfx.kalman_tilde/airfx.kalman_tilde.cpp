#include "ext.h"

#include "airfx.hpp"
#include "filter/kalman.hpp"

using TWrapped = airwindohhs::kalman::Kalman<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.kalman~", airwindohhs::kalman::k_long_description.data());
}
