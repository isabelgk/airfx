#include "c74_min.h"
#include "airfx.hpp"
#include "saturation/tube2.hpp"

using namespace c74::min;

class tube2_tilde : public airfx<tube2_tilde, airwindohhs::tube2::Tube2<double>>
{
    atom m_about_text = symbol{ airwindohhs::tube2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::tube2::k_name.data() };
    MIN_TAGS{ airwindohhs::tube2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    tube2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(tube2_tilde);
