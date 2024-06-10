#include "c74_min.h"
#include "airfx.hpp"
#include "effects/powersag.hpp"

using namespace c74::min;

class powersag_tilde : public airfx<powersag_tilde, airwindohhs::powersag::PowerSag<double>>
{
    atom m_about_text = symbol{ airwindohhs::powersag::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::powersag::k_name.data() };
    MIN_TAGS{ airwindohhs::powersag::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    powersag_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(powersag_tilde);
