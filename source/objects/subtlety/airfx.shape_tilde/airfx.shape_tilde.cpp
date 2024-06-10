#include "c74_min.h"
#include "airfx.hpp"
#include "subtlety/shape.hpp"

using namespace c74::min;

class shape_tilde : public airfx<shape_tilde, airwindohhs::shape::Shape<double>>
{
    atom m_about_text = symbol{ airwindohhs::shape::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::shape::k_name.data() };
    MIN_TAGS{ airwindohhs::shape::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    shape_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(shape_tilde);
