#include "ext.h"

#include "airfx.hpp"
#include "tape/fromtape.hpp"

using TWrapped = airwindohhs::fromtape::FromTape<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.fromtape~", airwindohhs::fromtape::k_long_description.data());
}
