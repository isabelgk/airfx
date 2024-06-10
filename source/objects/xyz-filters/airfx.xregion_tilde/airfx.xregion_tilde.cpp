#include "c74_min.h"
#include "airfx.hpp"
#include "xyz-filters/xregion.hpp"

using namespace c74::min;

class xregion_tilde : public airfx<xregion_tilde, airwindohhs::xregion::XRegion<double>>
{
    atom m_about_text = symbol{ airwindohhs::xregion::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::xregion::k_name.data() };
    MIN_TAGS{ airwindohhs::xregion::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    xregion_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(xregion_tilde);
