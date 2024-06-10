#include "c74_min.h"
#include "airfx.hpp"
#include "ambience/melt.hpp"

using namespace c74::min;

class melt_tilde : public airfx<melt_tilde, airwindohhs::melt::Melt<double>>
{
    atom m_about_text = symbol{ airwindohhs::melt::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::melt::k_name.data() };
    MIN_TAGS{ airwindohhs::melt::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    melt_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(melt_tilde);
