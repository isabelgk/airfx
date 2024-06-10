#include "c74_min.h"
#include "airfx.hpp"
#include "dithers/nodedither.hpp"

using namespace c74::min;

class nodedither_tilde : public airfx<nodedither_tilde, airwindohhs::nodedither::NodeDither<double>>
{
    atom m_about_text = symbol{ airwindohhs::nodedither::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::nodedither::k_name.data() };
    MIN_TAGS{ airwindohhs::nodedither::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    nodedither_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(nodedither_tilde);
