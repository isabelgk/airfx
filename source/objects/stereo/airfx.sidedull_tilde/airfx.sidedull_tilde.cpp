#include "c74_min.h"
#include "airfx.hpp"
#include "stereo/sidedull.hpp"

using namespace c74::min;

class sidedull_tilde : public airfx<sidedull_tilde, airwindohhs::sidedull::SideDull<double>>
{
    atom m_about_text = symbol{ airwindohhs::sidedull::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::sidedull::k_name.data() };
    MIN_TAGS{ airwindohhs::sidedull::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    sidedull_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(sidedull_tilde);
