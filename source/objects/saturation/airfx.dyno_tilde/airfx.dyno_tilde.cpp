#include "c74_min.h"
#include "airfx.hpp"
#include "saturation/dyno.hpp"

using namespace c74::min;

class dyno_tilde : public airfx<dyno_tilde, airwindohhs::dyno::Dyno<double>>
{
    atom m_about_text = symbol{ airwindohhs::dyno::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::dyno::k_name.data() };
    MIN_TAGS{ airwindohhs::dyno::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    dyno_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(dyno_tilde);
