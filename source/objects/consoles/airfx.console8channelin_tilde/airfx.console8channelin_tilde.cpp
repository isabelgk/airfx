#include "ext.h"

#include "airfx.hpp"
#include "consoles/console8channelin.hpp"

using TWrapped = airwindohhs::console8channelin::Console8ChannelIn<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console8channelin~", airwindohhs::console8channelin::k_long_description.data());
}
