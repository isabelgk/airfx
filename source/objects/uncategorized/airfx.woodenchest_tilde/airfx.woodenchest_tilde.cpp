#include "ext.h"

#include "airfx.hpp"
#include "uncategorized/woodenchest.hpp"

using TWrapped = airwindohhs::woodenchest::WoodenChest<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.woodenchest~", airwindohhs::woodenchest::k_long_description.data());
}
