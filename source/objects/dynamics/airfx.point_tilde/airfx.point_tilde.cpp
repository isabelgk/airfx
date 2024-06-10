#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/point.hpp"

using namespace c74::min;

class point_tilde : public airfx<point_tilde, airwindohhs::point::Point<double>>
{
    atom m_about_text = symbol{ airwindohhs::point::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::point::k_name.data() };
    MIN_TAGS{ airwindohhs::point::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    point_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(point_tilde);
