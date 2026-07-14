#include "ext.h"

#include "airfx.hpp"
#include "biquads/biquaddouble.hpp"

using TWrapped = airwindohhs::biquaddouble::BiquadDouble<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.biquaddouble~", airwindohhs::biquaddouble::k_long_description.data());
}
