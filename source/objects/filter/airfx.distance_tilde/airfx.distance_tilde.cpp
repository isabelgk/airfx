#include "c74_min.h"
#include "airfx.hpp"
#include "filter/distance.hpp"

using namespace c74::min;

class distance_tilde : public airfx<distance_tilde, airwindohhs::distance::Distance<double>>
{
    atom m_about_text = symbol{ airwindohhs::distance::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::distance::k_name.data() };
    MIN_TAGS{ airwindohhs::distance::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    distance_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(distance_tilde);
