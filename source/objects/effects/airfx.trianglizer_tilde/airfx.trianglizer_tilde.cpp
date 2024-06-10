#include "c74_min.h"
#include "airfx.hpp"
#include "effects/trianglizer.hpp"

using namespace c74::min;

class trianglizer_tilde : public airfx<trianglizer_tilde, airwindohhs::trianglizer::Trianglizer<double>>
{
    atom m_about_text = symbol{ airwindohhs::trianglizer::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::trianglizer::k_name.data() };
    MIN_TAGS{ airwindohhs::trianglizer::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    trianglizer_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(trianglizer_tilde);
