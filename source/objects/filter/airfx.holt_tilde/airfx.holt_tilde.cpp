#include "ext.h"

#include "airfx.hpp"
#include "filter/holt.hpp"

using TWrapped = airwindohhs::holt::Holt<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.holt~", airwindohhs::holt::k_long_description.data());
}
