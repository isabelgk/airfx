#include "c74_min.h"
#include "airfx.hpp"
#include "filter/stonefire.hpp"

using namespace c74::min;

class stonefire_tilde : public airfx<stonefire_tilde, airwindohhs::stonefire::Stonefire<double>>
{
    atom m_about_text = symbol{ airwindohhs::stonefire::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::stonefire::k_name.data() };
    MIN_TAGS{ airwindohhs::stonefire::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    stonefire_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(stonefire_tilde);
