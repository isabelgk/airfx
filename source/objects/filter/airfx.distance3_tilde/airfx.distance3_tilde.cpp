#include "c74_min.h"
#include "airfx.hpp"
#include "filter/distance3.hpp"

using namespace c74::min;

class distance3_tilde : public airfx<distance3_tilde, airwindohhs::distance3::Distance3<double>>
{
    atom m_about_text = symbol{ airwindohhs::distance3::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::distance3::k_name.data() };
    MIN_TAGS{ airwindohhs::distance3::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    distance3_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(distance3_tilde);
