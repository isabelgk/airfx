#include "ext.h"

#include "airfx.hpp"
#include "biquads/biquadplus.hpp"

using TWrapped = airwindohhs::biquadplus::BiquadPlus<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.biquadplus~", airwindohhs::biquadplus::k_long_description.data());
}
