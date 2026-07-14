#include "ext.h"

#include "airfx.hpp"
#include "dithers/rawglitters.hpp"

using TWrapped = airwindohhs::rawglitters::RawGlitters<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.rawglitters~", airwindohhs::rawglitters::k_long_description.data());
}
