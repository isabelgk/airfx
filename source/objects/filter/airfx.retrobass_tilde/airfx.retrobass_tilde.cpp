#include "ext.h"

#include "airfx.hpp"
#include "filter/retrobass.hpp"

using TWrapped = airwindohhs::retrobass::RetroBass<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.retrobass~", airwindohhs::retrobass::k_long_description.data());
}
