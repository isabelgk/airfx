#include "ext.h"

#include "airfx.hpp"
#include "effects/guitarconditioner.hpp"

using TWrapped = airwindohhs::guitarconditioner::GuitarConditioner<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.guitarconditioner~", airwindohhs::guitarconditioner::k_long_description.data());
}
