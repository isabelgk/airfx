#include "c74_min.h"
#include "airfx.hpp"
#include "ambience/mv.hpp"

using namespace c74::min;

class mv_tilde : public airfx<mv_tilde, airwindohhs::mv::MV<double>>
{
    atom m_about_text = symbol{ airwindohhs::mv::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::mv::k_name.data() };
    MIN_TAGS{ airwindohhs::mv::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    mv_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(mv_tilde);
