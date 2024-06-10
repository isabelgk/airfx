#include "c74_min.h"
#include "airfx.hpp"
#include "effects/powersag2.hpp"

using namespace c74::min;

class powersag2_tilde : public airfx<powersag2_tilde, airwindohhs::powersag2::PowerSag2<double>>
{
    atom m_about_text = symbol{ airwindohhs::powersag2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::powersag2::k_name.data() };
    MIN_TAGS{ airwindohhs::powersag2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    powersag2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(powersag2_tilde);
