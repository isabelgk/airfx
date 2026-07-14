#include "ext.h"

#include "airfx.hpp"
#include "brightness/hypersonic.hpp"

using TWrapped = airwindohhs::hypersonic::Hypersonic<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.hypersonic~", airwindohhs::hypersonic::k_long_description.data());
}
