#include "c74_min.h"
#include "airfx.hpp"
#include "xyz-filters/zhighpass.hpp"

using namespace c74::min;

class zhighpass_tilde : public airfx<zhighpass_tilde, airwindohhs::zhighpass::ZHighpass<double>>
{
    atom m_about_text = symbol{ airwindohhs::zhighpass::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::zhighpass::k_name.data() };
    MIN_TAGS{ airwindohhs::zhighpass::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    zhighpass_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(zhighpass_tilde);
