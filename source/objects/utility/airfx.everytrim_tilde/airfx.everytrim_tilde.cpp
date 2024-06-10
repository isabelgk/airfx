#include "c74_min.h"
#include "airfx.hpp"
#include "utility/everytrim.hpp"

using namespace c74::min;

class everytrim_tilde : public airfx<everytrim_tilde, airwindohhs::everytrim::EveryTrim<double>>
{
    atom m_about_text = symbol{ airwindohhs::everytrim::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::everytrim::k_name.data() };
    MIN_TAGS{ airwindohhs::everytrim::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    everytrim_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(everytrim_tilde);
