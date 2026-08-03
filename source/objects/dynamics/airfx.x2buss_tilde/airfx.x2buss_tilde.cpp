#include "ext.h"

#include "airfx.hpp"
#include "dynamics/x2buss.hpp"

using TWrapped = airwindohhs::x2buss::X2Buss<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.x2buss~", airwindohhs::x2buss::k_long_description.data());
}
