#include "ext.h"

#include "airfx.hpp"
#include "filter/suzan.hpp"

using TWrapped = airwindohhs::suzan::Suzan<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.suzan~", airwindohhs::suzan::k_long_description.data());
}
