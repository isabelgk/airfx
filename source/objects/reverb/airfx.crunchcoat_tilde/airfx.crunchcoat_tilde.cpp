#include "ext.h"

#include "airfx.hpp"
#include "reverb/crunchcoat.hpp"

using TWrapped = airwindohhs::crunchcoat::CrunchCoat<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.crunchcoat~", airwindohhs::crunchcoat::k_long_description.data());
}
