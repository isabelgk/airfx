#include "ext.h"

#include "airfx.hpp"
#include "filter/lowpass2.hpp"

using TWrapped = airwindohhs::lowpass2::Lowpass2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.lowpass2~", airwindohhs::lowpass2::k_long_description.data());
}
