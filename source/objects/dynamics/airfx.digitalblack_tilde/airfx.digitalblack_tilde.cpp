#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/digitalblack.hpp"

using namespace c74::min;

class digitalblack_tilde : public airfx<digitalblack_tilde, airwindohhs::digitalblack::DigitalBlack<double>>
{
    atom m_about_text = symbol{ airwindohhs::digitalblack::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::digitalblack::k_name.data() };
    MIN_TAGS{ airwindohhs::digitalblack::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    digitalblack_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(digitalblack_tilde);
