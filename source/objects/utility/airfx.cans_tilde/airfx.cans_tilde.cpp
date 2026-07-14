#include "ext.h"

#include "airfx.hpp"
#include "utility/cans.hpp"

using TWrapped = airwindohhs::cans::Cans<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.cans~", airwindohhs::cans::k_long_description.data());
}
