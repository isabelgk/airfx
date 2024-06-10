#include "c74_min.h"
#include "airfx.hpp"
#include "tone-color/channel9.hpp"

using namespace c74::min;

class channel9_tilde : public airfx<channel9_tilde, airwindohhs::channel9::Channel9<double>>
{
    atom m_about_text = symbol{ airwindohhs::channel9::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::channel9::k_name.data() };
    MIN_TAGS{ airwindohhs::channel9::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    channel9_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(channel9_tilde);
