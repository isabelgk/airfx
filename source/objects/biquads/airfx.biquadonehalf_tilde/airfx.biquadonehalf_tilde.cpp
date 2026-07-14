#include "ext.h"

#include "airfx.hpp"
#include "biquads/biquadonehalf.hpp"

using TWrapped = airwindohhs::biquadonehalf::BiquadOneHalf<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.biquadonehalf~", airwindohhs::biquadonehalf::k_long_description.data());
}
