#include "ext.h"

#include "airfx.hpp"
#include "subtlety/hype.hpp"

using TWrapped = airwindohhs::hype::Hype<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.hype~", airwindohhs::hype::k_long_description.data());
}
