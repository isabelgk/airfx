#include "ext.h"

#include "airfx.hpp"
#include "brightness/air3.hpp"

using TWrapped = airwindohhs::air3::Air3<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.air3~", airwindohhs::air3::k_long_description.data());
}
