#include "c74_min.h"
#include "airfx.hpp"
#include "saturation/spiral.hpp"

using namespace c74::min;

class spiral_tilde : public airfx<spiral_tilde, airwindohhs::spiral::Spiral<double>>
{
    atom m_about_text = symbol{ airwindohhs::spiral::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::spiral::k_name.data() };
    MIN_TAGS{ airwindohhs::spiral::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    spiral_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(spiral_tilde);
