#include "ext.h"

#include "airfx.hpp"
#include "reverb/creamcoat.hpp"

using TWrapped = airwindohhs::creamcoat::CreamCoat<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.creamcoat~", airwindohhs::creamcoat::k_long_description.data());
}
