#include "c74_min.h"
#include "airfx.hpp"
#include "ambience/tapedelay2.hpp"

using namespace c74::min;

class tapedelay2_tilde : public airfx<tapedelay2_tilde, airwindohhs::tapedelay2::TapeDelay2<double>>
{
    atom m_about_text = symbol{ airwindohhs::tapedelay2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::tapedelay2::k_name.data() };
    MIN_TAGS{ airwindohhs::tapedelay2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    tapedelay2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(tapedelay2_tilde);
