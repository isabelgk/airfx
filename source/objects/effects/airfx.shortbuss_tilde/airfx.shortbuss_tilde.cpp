#include "ext.h"

#include "airfx.hpp"
#include "effects/shortbuss.hpp"

using TWrapped = airwindohhs::shortbuss::ShortBuss<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.shortbuss~", airwindohhs::shortbuss::k_long_description.data());
}
