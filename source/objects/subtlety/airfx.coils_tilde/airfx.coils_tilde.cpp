#include "ext.h"

#include "airfx.hpp"
#include "subtlety/coils.hpp"

using TWrapped = airwindohhs::coils::Coils<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.coils~", airwindohhs::coils::k_long_description.data());
}
