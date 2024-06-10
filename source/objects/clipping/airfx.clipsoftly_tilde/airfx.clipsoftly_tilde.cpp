#include "c74_min.h"
#include "airfx.hpp"
#include "clipping/clipsoftly.hpp"

using namespace c74::min;

class clipsoftly_tilde : public airfx<clipsoftly_tilde, airwindohhs::clipsoftly::ClipSoftly<double>>
{
    atom m_about_text = symbol{ airwindohhs::clipsoftly::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::clipsoftly::k_name.data() };
    MIN_TAGS{ airwindohhs::clipsoftly::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    clipsoftly_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(clipsoftly_tilde);
