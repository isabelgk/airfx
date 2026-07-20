#include "ext.h"

#include "airfx.hpp"
#include "reverb/krockstar.hpp"

using TWrapped = airwindohhs::krockstar::kRockstar<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.krockstar~", airwindohhs::krockstar::k_long_description.data());
}
