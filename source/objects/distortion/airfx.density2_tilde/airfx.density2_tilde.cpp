#include "c74_min.h"
#include "airfx.hpp"
#include "distortion/density2.hpp"

using namespace c74::min;

class density2_tilde : public airfx<density2_tilde, airwindohhs::density2::Density2<double>>
{
    atom m_about_text = symbol{ airwindohhs::density2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::density2::k_name.data() };
    MIN_TAGS{ airwindohhs::density2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    density2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(density2_tilde);
