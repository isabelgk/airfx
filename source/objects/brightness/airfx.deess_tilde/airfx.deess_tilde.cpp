#include "ext.h"

#include "airfx.hpp"
#include "brightness/deess.hpp"

using TWrapped = airwindohhs::deess::DeEss<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.deess~", airwindohhs::deess::k_long_description.data());
}
