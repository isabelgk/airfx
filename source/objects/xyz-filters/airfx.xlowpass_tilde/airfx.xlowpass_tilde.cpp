#include "c74_min.h"
#include "airfx.hpp"
#include "xyz-filters/xlowpass.hpp"

using namespace c74::min;

class xlowpass_tilde : public airfx<xlowpass_tilde, airwindohhs::xlowpass::XLowpass<double>>
{
    atom m_about_text = symbol{ airwindohhs::xlowpass::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::xlowpass::k_name.data() };
    MIN_TAGS{ airwindohhs::xlowpass::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    xlowpass_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(xlowpass_tilde);
