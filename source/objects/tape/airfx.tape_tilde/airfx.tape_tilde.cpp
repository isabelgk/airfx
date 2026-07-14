#include "ext.h"

#include "airfx.hpp"
#include "tape/tape.hpp"

using TWrapped = airwindohhs::tape::Tape<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.tape~", airwindohhs::tape::k_long_description.data());
}
