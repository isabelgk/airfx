#include "c74_min.h"
#include "airfx.hpp"
#include "reverb/verbity2.hpp"

using namespace c74::min;

class verbity2_tilde : public airfx<verbity2_tilde, airwindohhs::verbity2::Verbity2<double>>
{
    atom m_about_text = symbol{ airwindohhs::verbity2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::verbity2::k_name.data() };
    MIN_TAGS{ airwindohhs::verbity2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    verbity2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(verbity2_tilde);
