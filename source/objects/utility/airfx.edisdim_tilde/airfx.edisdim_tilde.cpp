#include "ext.h"

#include "airfx.hpp"
#include "utility/edisdim.hpp"

using TWrapped = airwindohhs::edisdim::EdIsDim<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.edisdim~", airwindohhs::edisdim::k_long_description.data());
}
