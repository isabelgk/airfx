#include "ext.h"

#include "airfx.hpp"
#include "uncategorized/consolehpre.hpp"

using TWrapped = airwindohhs::consolehpre::ConsoleHPre<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.consolehpre~", airwindohhs::consolehpre::k_long_description.data());
}
