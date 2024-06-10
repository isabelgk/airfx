#include "c74_min.h"
#include "airfx.hpp"
#include "utility/contenthided.hpp"

using namespace c74::min;

class contenthided_tilde : public airfx<contenthided_tilde, airwindohhs::contenthided::ContentHideD<double>>
{
    atom m_about_text = symbol{ airwindohhs::contenthided::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::contenthided::k_name.data() };
    MIN_TAGS{ airwindohhs::contenthided::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    contenthided_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(contenthided_tilde);
