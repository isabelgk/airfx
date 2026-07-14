#include "ext.h"

#include "airfx.hpp"
#include "effects/takecare.hpp"

using TWrapped = airwindohhs::takecare::TakeCare<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.takecare~", airwindohhs::takecare::k_long_description.data());
}
