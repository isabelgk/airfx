#include "c74_min.h"
#include "airfx.hpp"
#include "noise/tapedust.hpp"

using namespace c74::min;

class tapedust_tilde : public airfx<tapedust_tilde, airwindohhs::tapedust::TapeDust<double>>
{
    atom m_about_text = symbol{ airwindohhs::tapedust::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::tapedust::k_name.data() };
    MIN_TAGS{ airwindohhs::tapedust::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    tapedust_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(tapedust_tilde);
