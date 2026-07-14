#include "ext.h"

#include "airfx.hpp"
#include "tone-color/woodenbox.hpp"

using TWrapped = airwindohhs::woodenbox::WoodenBox<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.woodenbox~", airwindohhs::woodenbox::k_long_description.data());
}
