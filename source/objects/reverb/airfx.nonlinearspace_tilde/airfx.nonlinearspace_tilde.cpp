#include "ext.h"

#include "airfx.hpp"
#include "reverb/nonlinearspace.hpp"

using TWrapped = airwindohhs::nonlinearspace::NonlinearSpace<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.nonlinearspace~", airwindohhs::nonlinearspace::k_long_description.data());
}
