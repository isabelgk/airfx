#include "c74_min.h"
#include "airfx.hpp"
#include "effects/gringer.hpp"

using namespace c74::min;

class gringer_tilde : public airfx<gringer_tilde, airwindohhs::gringer::Gringer<double>>
{
    atom m_about_text = symbol{ airwindohhs::gringer::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::gringer::k_name.data() };
    MIN_TAGS{ airwindohhs::gringer::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    gringer_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(gringer_tilde);
