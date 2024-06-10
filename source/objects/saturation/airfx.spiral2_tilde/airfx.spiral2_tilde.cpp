#include "c74_min.h"
#include "airfx.hpp"
#include "saturation/spiral2.hpp"

using namespace c74::min;

class spiral2_tilde : public airfx<spiral2_tilde, airwindohhs::spiral2::Spiral2<double>>
{
    atom m_about_text = symbol{ airwindohhs::spiral2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::spiral2::k_name.data() };
    MIN_TAGS{ airwindohhs::spiral2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    spiral2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(spiral2_tilde);
