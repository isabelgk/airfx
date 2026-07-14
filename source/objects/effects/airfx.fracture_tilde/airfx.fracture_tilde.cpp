#include "ext.h"

#include "airfx.hpp"
#include "effects/fracture.hpp"

using TWrapped = airwindohhs::fracture::Fracture<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.fracture~", airwindohhs::fracture::k_long_description.data());
}
