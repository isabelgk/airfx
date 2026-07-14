#include "ext.h"

#include "airfx.hpp"
#include "utility/balanced.hpp"

using TWrapped = airwindohhs::balanced::Balanced<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.balanced~", airwindohhs::balanced::k_long_description.data());
}
