#include "ext.h"

#include "airfx.hpp"
#include "uncategorized/consolexpre.hpp"

using TWrapped = airwindohhs::consolexpre::ConsoleXPre<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.consolexpre~", airwindohhs::consolexpre::k_long_description.data());
}
