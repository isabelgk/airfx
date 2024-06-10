#include "c74_min.h"
#include "airfx.hpp"
#include "lo-fi/cojones.hpp"

using namespace c74::min;

class cojones_tilde : public airfx<cojones_tilde, airwindohhs::cojones::Cojones<double>>
{
    atom m_about_text = symbol{ airwindohhs::cojones::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::cojones::k_name.data() };
    MIN_TAGS{ airwindohhs::cojones::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    cojones_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(cojones_tilde);
