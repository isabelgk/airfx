#include "c74_min.h"
#include "airfx.hpp"
#include "xyz-filters/zregion.hpp"

using namespace c74::min;

class zregion_tilde : public airfx<zregion_tilde, airwindohhs::zregion::ZRegion<double>>
{
    atom m_about_text = symbol{ airwindohhs::zregion::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::zregion::k_name.data() };
    MIN_TAGS{ airwindohhs::zregion::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    zregion_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(zregion_tilde);
