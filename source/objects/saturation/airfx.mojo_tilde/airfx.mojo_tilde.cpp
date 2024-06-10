#include "c74_min.h"
#include "airfx.hpp"
#include "saturation/mojo.hpp"

using namespace c74::min;

class mojo_tilde : public airfx<mojo_tilde, airwindohhs::mojo::Mojo<double>>
{
    atom m_about_text = symbol{ airwindohhs::mojo::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::mojo::k_name.data() };
    MIN_TAGS{ airwindohhs::mojo::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    mojo_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(mojo_tilde);
