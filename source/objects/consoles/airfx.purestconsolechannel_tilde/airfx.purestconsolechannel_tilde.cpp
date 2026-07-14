#include "ext.h"

#include "airfx.hpp"
#include "consoles/purestconsolechannel.hpp"

using TWrapped = airwindohhs::purestconsolechannel::PurestConsoleChannel<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.purestconsolechannel~", airwindohhs::purestconsolechannel::k_long_description.data());
}
