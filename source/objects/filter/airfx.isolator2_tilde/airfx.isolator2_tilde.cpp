#include "ext.h"

#include "airfx.hpp"
#include "filter/isolator2.hpp"

using TWrapped = airwindohhs::isolator2::Isolator2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.isolator2~", airwindohhs::isolator2::k_long_description.data());
}
