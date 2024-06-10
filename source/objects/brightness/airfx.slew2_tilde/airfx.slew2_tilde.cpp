#include "c74_min.h"
#include "airfx.hpp"
#include "brightness/slew2.hpp"

using namespace c74::min;

class slew2_tilde : public airfx<slew2_tilde, airwindohhs::slew2::Slew2<double>>
{
    atom m_about_text = symbol{ airwindohhs::slew2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::slew2::k_name.data() };
    MIN_TAGS{ airwindohhs::slew2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    slew2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(slew2_tilde);
