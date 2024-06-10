#include "c74_min.h"
#include "airfx.hpp"
#include "stereo/lrfliptimer.hpp"

using namespace c74::min;

class lrfliptimer_tilde : public airfx<lrfliptimer_tilde, airwindohhs::lrfliptimer::LRFlipTimer<double>>
{
    atom m_about_text = symbol{ airwindohhs::lrfliptimer::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::lrfliptimer::k_name.data() };
    MIN_TAGS{ airwindohhs::lrfliptimer::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    lrfliptimer_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(lrfliptimer_tilde);
