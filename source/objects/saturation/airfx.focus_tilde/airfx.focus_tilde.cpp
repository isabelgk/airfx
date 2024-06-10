#include "c74_min.h"
#include "airfx.hpp"
#include "saturation/focus.hpp"

using namespace c74::min;

class focus_tilde : public airfx<focus_tilde, airwindohhs::focus::Focus<double>>
{
    atom m_about_text = symbol{ airwindohhs::focus::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::focus::k_name.data() };
    MIN_TAGS{ airwindohhs::focus::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    focus_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(focus_tilde);
