#include "c74_min.h"
#include "airfx.hpp"
#include "xyz-filters/znotch2.hpp"

using namespace c74::min;

class znotch2_tilde : public airfx<znotch2_tilde, airwindohhs::znotch2::ZNotch2<double>>
{
    atom m_about_text = symbol{ airwindohhs::znotch2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::znotch2::k_name.data() };
    MIN_TAGS{ airwindohhs::znotch2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    znotch2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(znotch2_tilde);
