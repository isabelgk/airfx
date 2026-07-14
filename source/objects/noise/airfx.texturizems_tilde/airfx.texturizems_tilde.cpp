#include "ext.h"

#include "airfx.hpp"
#include "noise/texturizems.hpp"

using TWrapped = airwindohhs::texturizems::TexturizeMS<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.texturizems~", airwindohhs::texturizems::k_long_description.data());
}
