#include "ext.h"

#include "airfx.hpp"
#include "uncategorized/consolex3.hpp"

using TWrapped = airwindohhs::consolex3::ConsoleX3<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.consolex3~", airwindohhs::consolex3::k_long_description.data());
}
