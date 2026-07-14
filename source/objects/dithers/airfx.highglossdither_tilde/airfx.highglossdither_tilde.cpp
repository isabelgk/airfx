#include "ext.h"

#include "airfx.hpp"
#include "dithers/highglossdither.hpp"

using TWrapped = airwindohhs::highglossdither::HighGlossDither<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.highglossdither~", airwindohhs::highglossdither::k_long_description.data());
}
