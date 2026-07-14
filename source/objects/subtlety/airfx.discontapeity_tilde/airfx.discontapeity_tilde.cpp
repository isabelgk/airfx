#include "ext.h"

#include "airfx.hpp"
#include "subtlety/discontapeity.hpp"

using TWrapped = airwindohhs::discontapeity::Discontapeity<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.discontapeity~", airwindohhs::discontapeity::k_long_description.data());
}
