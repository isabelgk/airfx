#include "ext.h"

#include "airfx.hpp"
#include "distortion/loud.hpp"

using TWrapped = airwindohhs::loud::Loud<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.loud~", airwindohhs::loud::k_long_description.data());
}
