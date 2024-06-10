#include "c74_min.h"
#include "airfx.hpp"
#include "dithers/highglossdither.hpp"

using namespace c74::min;

class highglossdither_tilde : public airfx<highglossdither_tilde, airwindohhs::highglossdither::HighGlossDither<double>>
{
    atom m_about_text = symbol{ airwindohhs::highglossdither::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::highglossdither::k_name.data() };
    MIN_TAGS{ airwindohhs::highglossdither::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    highglossdither_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(highglossdither_tilde);
