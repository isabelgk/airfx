#include "ext.h"

#include "airfx.hpp"
#include "biquads/biquad2.hpp"

using TWrapped = airwindohhs::biquad2::Biquad2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.biquad2~", airwindohhs::biquad2::k_long_description.data());
}
