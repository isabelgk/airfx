#include "c74_min.h"
#include "airfx.hpp"
#include "utility/slewonly.hpp"

using namespace c74::min;

class slewonly_tilde : public airfx<slewonly_tilde, airwindohhs::slewonly::SlewOnly<double>>
{
    atom m_about_text = symbol{ airwindohhs::slewonly::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::slewonly::k_name.data() };
    MIN_TAGS{ airwindohhs::slewonly::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    slewonly_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(slewonly_tilde);
