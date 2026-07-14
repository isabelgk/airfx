#include "ext.h"

#include "airfx.hpp"
#include "tone-color/cider.hpp"

using TWrapped = airwindohhs::cider::Cider<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.cider~", airwindohhs::cider::k_long_description.data());
}
