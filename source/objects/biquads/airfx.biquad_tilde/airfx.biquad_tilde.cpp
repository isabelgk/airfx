#include "ext.h"

#include "airfx.hpp"
#include "biquads/biquad.hpp"

using TWrapped = airwindohhs::biquad::Biquad<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.biquad~", airwindohhs::biquad::k_long_description.data());
}
