#include "ext.h"

#include "airfx.hpp"
#include "biquads/biquadtriple.hpp"

using TWrapped = airwindohhs::biquadtriple::BiquadTriple<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.biquadtriple~", airwindohhs::biquadtriple::k_long_description.data());
}
