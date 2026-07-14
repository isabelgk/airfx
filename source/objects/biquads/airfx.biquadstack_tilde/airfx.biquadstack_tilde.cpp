#include "ext.h"

#include "airfx.hpp"
#include "biquads/biquadstack.hpp"

using TWrapped = airwindohhs::biquadstack::BiquadStack<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.biquadstack~", airwindohhs::biquadstack::k_long_description.data());
}
