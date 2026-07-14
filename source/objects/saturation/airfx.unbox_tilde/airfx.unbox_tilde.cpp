#include "ext.h"

#include "airfx.hpp"
#include "saturation/unbox.hpp"

using TWrapped = airwindohhs::unbox::UnBox<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.unbox~", airwindohhs::unbox::k_long_description.data());
}
