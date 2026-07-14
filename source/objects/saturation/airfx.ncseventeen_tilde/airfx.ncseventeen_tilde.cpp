#include "ext.h"

#include "airfx.hpp"
#include "saturation/ncseventeen.hpp"

using TWrapped = airwindohhs::ncseventeen::NCSeventeen<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.ncseventeen~", airwindohhs::ncseventeen::k_long_description.data());
}
