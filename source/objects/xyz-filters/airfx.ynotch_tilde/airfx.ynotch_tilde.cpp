#include "c74_min.h"
#include "airfx.hpp"
#include "xyz-filters/ynotch.hpp"

using namespace c74::min;

class ynotch_tilde : public airfx<ynotch_tilde, airwindohhs::ynotch::YNotch<double>>
{
    atom m_about_text = symbol{ airwindohhs::ynotch::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::ynotch::k_name.data() };
    MIN_TAGS{ airwindohhs::ynotch::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    ynotch_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(ynotch_tilde);
