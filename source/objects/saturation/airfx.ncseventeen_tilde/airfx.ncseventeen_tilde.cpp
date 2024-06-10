#include "c74_min.h"
#include "airfx.hpp"
#include "saturation/ncseventeen.hpp"

using namespace c74::min;

class ncseventeen_tilde : public airfx<ncseventeen_tilde, airwindohhs::ncseventeen::NCSeventeen<double>>
{
    atom m_about_text = symbol{ airwindohhs::ncseventeen::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::ncseventeen::k_name.data() };
    MIN_TAGS{ airwindohhs::ncseventeen::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    ncseventeen_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(ncseventeen_tilde);
