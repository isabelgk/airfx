#include "c74_min.h"
#include "airfx.hpp"
#include "xyz-filters/znotch.hpp"

using namespace c74::min;

class znotch_tilde : public airfx<znotch_tilde, airwindohhs::znotch::ZNotch<double>>
{
    atom m_about_text = symbol{ airwindohhs::znotch::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::znotch::k_name.data() };
    MIN_TAGS{ airwindohhs::znotch::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    znotch_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(znotch_tilde);
