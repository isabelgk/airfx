#include "ext.h"

#include "airfx.hpp"
#include "lo-fi/pockey.hpp"

using TWrapped = airwindohhs::pockey::Pockey<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.pockey~", airwindohhs::pockey::k_long_description.data());
}
