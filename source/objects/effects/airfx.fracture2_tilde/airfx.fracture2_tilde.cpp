#include "ext.h"

#include "airfx.hpp"
#include "effects/fracture2.hpp"

using TWrapped = airwindohhs::fracture2::Fracture2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.fracture2~", airwindohhs::fracture2::k_long_description.data());
}
