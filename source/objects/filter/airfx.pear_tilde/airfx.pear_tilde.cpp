#include "ext.h"

#include "airfx.hpp"
#include "filter/pear.hpp"

using TWrapped = airwindohhs::pear::Pear<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.pear~", airwindohhs::pear::k_long_description.data());
}
