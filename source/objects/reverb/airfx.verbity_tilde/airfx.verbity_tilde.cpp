#include "c74_min.h"
#include "airfx.hpp"
#include "reverb/verbity.hpp"

using namespace c74::min;

class verbity_tilde : public airfx<verbity_tilde, airwindohhs::verbity::Verbity<double>>
{
    atom m_about_text = symbol{ airwindohhs::verbity::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::verbity::k_name.data() };
    MIN_TAGS{ airwindohhs::verbity::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    verbity_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(verbity_tilde);
