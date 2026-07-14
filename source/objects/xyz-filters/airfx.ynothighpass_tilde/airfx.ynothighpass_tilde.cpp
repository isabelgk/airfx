#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/ynothighpass.hpp"

using TWrapped = airwindohhs::ynothighpass::YNotHighpass<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.ynothighpass~", airwindohhs::ynothighpass::k_long_description.data());
}
