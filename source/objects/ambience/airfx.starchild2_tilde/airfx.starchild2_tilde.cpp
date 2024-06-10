#include "c74_min.h"
#include "airfx.hpp"
#include "ambience/starchild2.hpp"

using namespace c74::min;

class starchild2_tilde : public airfx<starchild2_tilde, airwindohhs::starchild2::StarChild2<double>>
{
    atom m_about_text = symbol{ airwindohhs::starchild2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::starchild2::k_name.data() };
    MIN_TAGS{ airwindohhs::starchild2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    starchild2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(starchild2_tilde);
