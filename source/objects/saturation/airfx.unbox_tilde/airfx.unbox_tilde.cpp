#include "c74_min.h"
#include "airfx.hpp"
#include "saturation/unbox.hpp"

using namespace c74::min;

class unbox_tilde : public airfx<unbox_tilde, airwindohhs::unbox::UnBox<double>>
{
    atom m_about_text = symbol{ airwindohhs::unbox::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::unbox::k_name.data() };
    MIN_TAGS{ airwindohhs::unbox::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    unbox_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(unbox_tilde);
