#include "c74_min.h"
#include "airfx.hpp"
#include "xyz-filters/ylowpass.hpp"

using namespace c74::min;

class ylowpass_tilde : public airfx<ylowpass_tilde, airwindohhs::ylowpass::YLowpass<double>>
{
    atom m_about_text = symbol{ airwindohhs::ylowpass::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::ylowpass::k_name.data() };
    MIN_TAGS{ airwindohhs::ylowpass::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    ylowpass_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(ylowpass_tilde);
