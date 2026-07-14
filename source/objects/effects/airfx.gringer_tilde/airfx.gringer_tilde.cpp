#include "ext.h"

#include "airfx.hpp"
#include "effects/gringer.hpp"

using TWrapped = airwindohhs::gringer::Gringer<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.gringer~", airwindohhs::gringer::k_long_description.data());
}
