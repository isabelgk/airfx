#include "ext.h"

#include "airfx.hpp"
#include "filter/highpass2.hpp"

using TWrapped = airwindohhs::highpass2::Highpass2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.highpass2~", airwindohhs::highpass2::k_long_description.data());
}
