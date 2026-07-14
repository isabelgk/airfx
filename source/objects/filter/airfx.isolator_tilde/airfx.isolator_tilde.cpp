#include "ext.h"

#include "airfx.hpp"
#include "filter/isolator.hpp"

using TWrapped = airwindohhs::isolator::Isolator<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.isolator~", airwindohhs::isolator::k_long_description.data());
}
