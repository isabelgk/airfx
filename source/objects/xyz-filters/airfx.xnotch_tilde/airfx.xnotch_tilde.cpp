#include "c74_min.h"
#include "airfx.hpp"
#include "xyz-filters/xnotch.hpp"

using namespace c74::min;

class xnotch_tilde : public airfx<xnotch_tilde, airwindohhs::xnotch::XNotch<double>>
{
    atom m_about_text = symbol{ airwindohhs::xnotch::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::xnotch::k_name.data() };
    MIN_TAGS{ airwindohhs::xnotch::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    xnotch_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(xnotch_tilde);
