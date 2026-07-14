#include "ext.h"

#include "airfx.hpp"
#include "utility/ulawdecode.hpp"

using TWrapped = airwindohhs::ulawdecode::uLawDecode<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.ulawdecode~", airwindohhs::ulawdecode::k_long_description.data());
}
