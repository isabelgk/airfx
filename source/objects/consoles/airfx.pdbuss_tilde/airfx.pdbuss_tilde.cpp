#include "ext.h"

#include "airfx.hpp"
#include "consoles/pdbuss.hpp"

using TWrapped = airwindohhs::pdbuss::PDBuss<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.pdbuss~", airwindohhs::pdbuss::k_long_description.data());
}
