#include "c74_min.h"
#include "airfx.hpp"
#include "distortion/multibanddistortion.hpp"

using namespace c74::min;

class multibanddistortion_tilde : public airfx<multibanddistortion_tilde, airwindohhs::multibanddistortion::MultiBandDistortion<double>>
{
    atom m_about_text = symbol{ airwindohhs::multibanddistortion::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::multibanddistortion::k_name.data() };
    MIN_TAGS{ airwindohhs::multibanddistortion::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    multibanddistortion_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(multibanddistortion_tilde);
