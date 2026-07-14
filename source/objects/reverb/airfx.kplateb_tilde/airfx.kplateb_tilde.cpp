#include "ext.h"

#include "airfx.hpp"
#include "reverb/kplateb.hpp"

using TWrapped = airwindohhs::kplateb::kPlateB<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.kplateb~", airwindohhs::kplateb::k_long_description.data());
}
