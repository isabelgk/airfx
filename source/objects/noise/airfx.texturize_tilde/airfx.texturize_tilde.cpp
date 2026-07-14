#include "ext.h"

#include "airfx.hpp"
#include "noise/texturize.hpp"

using TWrapped = airwindohhs::texturize::Texturize<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.texturize~", airwindohhs::texturize::k_long_description.data());
}
