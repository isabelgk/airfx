#include "c74_min.h"
#include "airfx.hpp"
#include "stereo/autopan.hpp"

using namespace c74::min;

class autopan_tilde : public airfx<autopan_tilde, airwindohhs::autopan::AutoPan<double>>
{
    atom m_about_text = symbol{ airwindohhs::autopan::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::autopan::k_name.data() };
    MIN_TAGS{ airwindohhs::autopan::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    autopan_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(autopan_tilde);
