#include "c74_min.h"
#include "airfx.hpp"
#include "subtlety/discontinuity.hpp"

using namespace c74::min;

class discontinuity_tilde : public airfx<discontinuity_tilde, airwindohhs::discontinuity::Discontinuity<double>>
{
    atom m_about_text = symbol{ airwindohhs::discontinuity::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::discontinuity::k_name.data() };
    MIN_TAGS{ airwindohhs::discontinuity::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    discontinuity_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(discontinuity_tilde);
