#include "ext.h"

#include "airfx.hpp"
#include "lo-fi/pockey2.hpp"

using TWrapped = airwindohhs::pockey2::Pockey2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.pockey2~", airwindohhs::pockey2::k_long_description.data());
}
