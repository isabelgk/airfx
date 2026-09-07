#include "ext.h"

#include "airfx.hpp"
#include "filter/fastdistance.hpp"

using TWrapped = airwindohhs::fastdistance::FastDistance<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.fastdistance~", airwindohhs::fastdistance::k_long_description.data());
}
