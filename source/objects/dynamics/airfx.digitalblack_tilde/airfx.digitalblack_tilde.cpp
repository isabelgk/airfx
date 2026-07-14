#include "ext.h"

#include "airfx.hpp"
#include "dynamics/digitalblack.hpp"

using TWrapped = airwindohhs::digitalblack::DigitalBlack<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.digitalblack~", airwindohhs::digitalblack::k_long_description.data());
}
