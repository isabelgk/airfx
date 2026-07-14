#include "ext.h"

#include "airfx.hpp"
#include "filter/angleeq.hpp"

using TWrapped = airwindohhs::angleeq::AngleEQ<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.angleeq~", airwindohhs::angleeq::k_long_description.data());
}
