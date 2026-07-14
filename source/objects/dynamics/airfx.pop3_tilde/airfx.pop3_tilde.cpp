#include "ext.h"

#include "airfx.hpp"
#include "dynamics/pop3.hpp"

using TWrapped = airwindohhs::pop3::Pop3<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.pop3~", airwindohhs::pop3::k_long_description.data());
}
