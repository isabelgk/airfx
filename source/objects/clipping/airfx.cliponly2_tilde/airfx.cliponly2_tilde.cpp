#include "c74_min.h"
#include "airfx.hpp"
#include "clipping/cliponly2.hpp"

using namespace c74::min;

class cliponly2_tilde : public airfx<cliponly2_tilde, airwindohhs::cliponly2::ClipOnly2<double>>
{
    atom m_about_text = symbol{ airwindohhs::cliponly2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::cliponly2::k_name.data() };
    MIN_TAGS{ airwindohhs::cliponly2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    cliponly2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(cliponly2_tilde);
