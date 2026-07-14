#include "ext.h"

#include "airfx.hpp"
#include "dithers/nodedither.hpp"

using TWrapped = airwindohhs::nodedither::NodeDither<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.nodedither~", airwindohhs::nodedither::k_long_description.data());
}
