#include "ext.h"

#include "airfx.hpp"
#include "dithers/notjustanotherdither.hpp"

using TWrapped = airwindohhs::notjustanotherdither::NotJustAnotherDither<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.notjustanotherdither~", airwindohhs::notjustanotherdither::k_long_description.data());
}
