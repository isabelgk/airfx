#include "ext.h"

#include "airfx.hpp"
#include "utility/peaksonly.hpp"

using TWrapped = airwindohhs::peaksonly::PeaksOnly<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.peaksonly~", airwindohhs::peaksonly::k_long_description.data());
}
