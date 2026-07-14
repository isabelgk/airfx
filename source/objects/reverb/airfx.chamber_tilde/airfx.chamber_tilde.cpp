#include "ext.h"

#include "airfx.hpp"
#include "reverb/chamber.hpp"

using TWrapped = airwindohhs::chamber::Chamber<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.chamber~", airwindohhs::chamber::k_long_description.data());
}
