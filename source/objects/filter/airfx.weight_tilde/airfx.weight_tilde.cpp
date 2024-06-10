#include "c74_min.h"
#include "airfx.hpp"
#include "filter/weight.hpp"

using namespace c74::min;

class weight_tilde : public airfx<weight_tilde, airwindohhs::weight::Weight<double>>
{
    atom m_about_text = symbol{ airwindohhs::weight::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::weight::k_name.data() };
    MIN_TAGS{ airwindohhs::weight::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    weight_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(weight_tilde);
