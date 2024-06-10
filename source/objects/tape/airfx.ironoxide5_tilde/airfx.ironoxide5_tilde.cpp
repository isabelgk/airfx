#include "c74_min.h"
#include "airfx.hpp"
#include "tape/ironoxide5.hpp"

using namespace c74::min;

class ironoxide5_tilde : public airfx<ironoxide5_tilde, airwindohhs::ironoxide5::IronOxide5<double>>
{
    atom m_about_text = symbol{ airwindohhs::ironoxide5::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::ironoxide5::k_name.data() };
    MIN_TAGS{ airwindohhs::ironoxide5::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    ironoxide5_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(ironoxide5_tilde);
