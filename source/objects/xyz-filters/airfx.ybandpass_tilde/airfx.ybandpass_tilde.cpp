#include "c74_min.h"
#include "airfx.hpp"
#include "xyz-filters/ybandpass.hpp"

using namespace c74::min;

class ybandpass_tilde : public airfx<ybandpass_tilde, airwindohhs::ybandpass::YBandpass<double>>
{
    atom m_about_text = symbol{ airwindohhs::ybandpass::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::ybandpass::k_name.data() };
    MIN_TAGS{ airwindohhs::ybandpass::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    ybandpass_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(ybandpass_tilde);
