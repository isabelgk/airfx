#include "c74_min.h"
#include "airfx.hpp"
#include "brightness/smooth.hpp"

using namespace c74::min;

class smooth_tilde : public airfx<smooth_tilde, airwindohhs::smooth::Smooth<double>>
{
    atom m_about_text = symbol{ airwindohhs::smooth::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::smooth::k_name.data() };
    MIN_TAGS{ airwindohhs::smooth::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    smooth_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(smooth_tilde);
