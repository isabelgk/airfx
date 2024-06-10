#include "c74_min.h"
#include "airfx.hpp"
#include "saturation/tube.hpp"

using namespace c74::min;

class tube_tilde : public airfx<tube_tilde, airwindohhs::tube::Tube<double>>
{
    atom m_about_text = symbol{ airwindohhs::tube::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::tube::k_name.data() };
    MIN_TAGS{ airwindohhs::tube::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    tube_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(tube_tilde);
