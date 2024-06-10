#include "c74_min.h"
#include "airfx.hpp"
#include "bass/floor.hpp"

using namespace c74::min;

class floor_tilde : public airfx<floor_tilde, airwindohhs::floor::Floor<double>>
{
    atom m_about_text = symbol{ airwindohhs::floor::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::floor::k_name.data() };
    MIN_TAGS{ airwindohhs::floor::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    floor_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(floor_tilde);
