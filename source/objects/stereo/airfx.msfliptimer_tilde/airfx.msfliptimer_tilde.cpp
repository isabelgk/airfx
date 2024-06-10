#include "c74_min.h"
#include "airfx.hpp"
#include "stereo/msfliptimer.hpp"

using namespace c74::min;

class msfliptimer_tilde : public airfx<msfliptimer_tilde, airwindohhs::msfliptimer::MSFlipTimer<double>>
{
    atom m_about_text = symbol{ airwindohhs::msfliptimer::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::msfliptimer::k_name.data() };
    MIN_TAGS{ airwindohhs::msfliptimer::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    msfliptimer_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(msfliptimer_tilde);
