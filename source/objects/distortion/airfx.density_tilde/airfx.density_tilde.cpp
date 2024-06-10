#include "c74_min.h"
#include "airfx.hpp"
#include "distortion/density.hpp"

using namespace c74::min;

class density_tilde : public airfx<density_tilde, airwindohhs::density::Density<double>>
{
    atom m_about_text = symbol{ airwindohhs::density::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::density::k_name.data() };
    MIN_TAGS{ airwindohhs::density::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    density_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(density_tilde);
