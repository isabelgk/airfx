#include "ext.h"

#include "airfx.hpp"
#include "dithers/tpdfwide.hpp"

using TWrapped = airwindohhs::tpdfwide::TPDFWide<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.tpdfwide~", airwindohhs::tpdfwide::k_long_description.data());
}
