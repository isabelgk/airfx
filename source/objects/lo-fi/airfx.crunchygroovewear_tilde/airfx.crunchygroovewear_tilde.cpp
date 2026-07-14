#include "ext.h"

#include "airfx.hpp"
#include "lo-fi/crunchygroovewear.hpp"

using TWrapped = airwindohhs::crunchygroovewear::CrunchyGrooveWear<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.crunchygroovewear~", airwindohhs::crunchygroovewear::k_long_description.data());
}
