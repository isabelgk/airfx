#include "c74_min.h"
#include "airfx.hpp"
#include "xyz-filters/zlowpass.hpp"

using namespace c74::min;

class zlowpass_tilde : public airfx<zlowpass_tilde, airwindohhs::zlowpass::ZLowpass<double>>
{
    atom m_about_text = symbol{ airwindohhs::zlowpass::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::zlowpass::k_name.data() };
    MIN_TAGS{ airwindohhs::zlowpass::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    zlowpass_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(zlowpass_tilde);
