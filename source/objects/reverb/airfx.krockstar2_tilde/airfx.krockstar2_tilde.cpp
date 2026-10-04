#include "ext.h"

#include "airfx.hpp"
#include "reverb/krockstar2.hpp"

using TWrapped = airwindohhs::krockstar2::kRockstar2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.krockstar2~", airwindohhs::krockstar2::k_long_description.data());
}
