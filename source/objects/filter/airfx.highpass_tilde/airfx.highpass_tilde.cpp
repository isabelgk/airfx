#include "ext.h"

#include "airfx.hpp"
#include "filter/highpass.hpp"

using TWrapped = airwindohhs::highpass::Highpass<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.highpass~", airwindohhs::highpass::k_long_description.data());
}
