#include "ext.h"

#include "airfx.hpp"
#include "dithers/dark.hpp"

using TWrapped = airwindohhs::dark::Dark<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.dark~", airwindohhs::dark::k_long_description.data());
}
