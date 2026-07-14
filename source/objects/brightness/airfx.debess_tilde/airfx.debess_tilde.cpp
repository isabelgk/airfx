#include "ext.h"

#include "airfx.hpp"
#include "brightness/debess.hpp"

using TWrapped = airwindohhs::debess::DeBess<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.debess~", airwindohhs::debess::k_long_description.data());
}
