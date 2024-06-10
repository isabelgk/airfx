#include "c74_min.h"
#include "airfx.hpp"
#include "reverb/galactic.hpp"

using namespace c74::min;

class galactic_tilde : public airfx<galactic_tilde, airwindohhs::galactic::Galactic<double>>
{
    atom m_about_text = symbol{ airwindohhs::galactic::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::galactic::k_name.data() };
    MIN_TAGS{ airwindohhs::galactic::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    galactic_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(galactic_tilde);
