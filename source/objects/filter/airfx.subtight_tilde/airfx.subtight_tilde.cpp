#include "ext.h"

#include "airfx.hpp"
#include "filter/subtight.hpp"

using TWrapped = airwindohhs::subtight::SubTight<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.subtight~", airwindohhs::subtight::k_long_description.data());
}
