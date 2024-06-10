#include "c74_min.h"
#include "airfx.hpp"
#include "tone-color/neverland.hpp"

using namespace c74::min;

class neverland_tilde : public airfx<neverland_tilde, airwindohhs::neverland::Neverland<double>>
{
    atom m_about_text = symbol{ airwindohhs::neverland::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::neverland::k_name.data() };
    MIN_TAGS{ airwindohhs::neverland::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    neverland_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(neverland_tilde);
