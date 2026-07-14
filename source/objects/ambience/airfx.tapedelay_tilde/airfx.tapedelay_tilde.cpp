#include "ext.h"

#include "airfx.hpp"
#include "ambience/tapedelay.hpp"

using TWrapped = airwindohhs::tapedelay::TapeDelay<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.tapedelay~", airwindohhs::tapedelay::k_long_description.data());
}
