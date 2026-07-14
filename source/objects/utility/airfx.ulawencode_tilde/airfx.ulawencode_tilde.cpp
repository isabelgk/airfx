#include "ext.h"

#include "airfx.hpp"
#include "utility/ulawencode.hpp"

using TWrapped = airwindohhs::ulawencode::uLawEncode<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.ulawencode~", airwindohhs::ulawencode::k_long_description.data());
}
