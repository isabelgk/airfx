#include "c74_min.h"
#include "airfx.hpp"
#include "clipping/cliponly.hpp"

using namespace c74::min;

class cliponly_tilde : public airfx<cliponly_tilde, airwindohhs::cliponly::ClipOnly<double>>
{
    atom m_about_text = symbol{ airwindohhs::cliponly::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::cliponly::k_name.data() };
    MIN_TAGS{ airwindohhs::cliponly::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    cliponly_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(cliponly_tilde);
