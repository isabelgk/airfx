#include "ext.h"

#include "airfx.hpp"
#include "effects/tremosquare.hpp"

using TWrapped = airwindohhs::tremosquare::TremoSquare<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.tremosquare~", airwindohhs::tremosquare::k_long_description.data());
}
