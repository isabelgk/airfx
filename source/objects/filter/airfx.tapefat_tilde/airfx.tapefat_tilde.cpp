#include "c74_min.h"
#include "airfx.hpp"
#include "filter/tapefat.hpp"

using namespace c74::min;

class tapefat_tilde : public airfx<tapefat_tilde, airwindohhs::tapefat::TapeFat<double>>
{
    atom m_about_text = symbol{ airwindohhs::tapefat::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::tapefat::k_name.data() };
    MIN_TAGS{ airwindohhs::tapefat::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    tapefat_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(tapefat_tilde);
