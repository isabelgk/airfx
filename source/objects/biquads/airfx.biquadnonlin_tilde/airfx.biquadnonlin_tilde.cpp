#include "ext.h"

#include "airfx.hpp"
#include "biquads/biquadnonlin.hpp"

using TWrapped = airwindohhs::biquadnonlin::BiquadNonLin<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.biquadnonlin~", airwindohhs::biquadnonlin::k_long_description.data());
}
