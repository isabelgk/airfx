#include "c74_min.h"
#include "airfx.hpp"
#include "ambience/starchild.hpp"

using namespace c74::min;

class starchild_tilde : public airfx<starchild_tilde, airwindohhs::starchild::StarChild<double>>
{
    atom m_about_text = symbol{ airwindohhs::starchild::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::starchild::k_name.data() };
    MIN_TAGS{ airwindohhs::starchild::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    starchild_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(starchild_tilde);
