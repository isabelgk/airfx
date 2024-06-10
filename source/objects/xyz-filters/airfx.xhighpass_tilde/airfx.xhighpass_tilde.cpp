#include "c74_min.h"
#include "airfx.hpp"
#include "xyz-filters/xhighpass.hpp"

using namespace c74::min;

class xhighpass_tilde : public airfx<xhighpass_tilde, airwindohhs::xhighpass::XHighpass<double>>
{
    atom m_about_text = symbol{ airwindohhs::xhighpass::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::xhighpass::k_name.data() };
    MIN_TAGS{ airwindohhs::xhighpass::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    xhighpass_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(xhighpass_tilde);
