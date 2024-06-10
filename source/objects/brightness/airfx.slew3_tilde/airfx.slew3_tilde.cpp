#include "c74_min.h"
#include "airfx.hpp"
#include "brightness/slew3.hpp"

using namespace c74::min;

class slew3_tilde : public airfx<slew3_tilde, airwindohhs::slew3::Slew3<double>>
{
    atom m_about_text = symbol{ airwindohhs::slew3::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::slew3::k_name.data() };
    MIN_TAGS{ airwindohhs::slew3::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    slew3_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(slew3_tilde);
