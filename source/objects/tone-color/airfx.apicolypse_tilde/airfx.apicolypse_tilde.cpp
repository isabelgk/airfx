#include "c74_min.h"
#include "airfx.hpp"
#include "tone-color/apicolypse.hpp"

using namespace c74::min;

class apicolypse_tilde : public airfx<apicolypse_tilde, airwindohhs::apicolypse::Apicolypse<double>>
{
    atom m_about_text = symbol{ airwindohhs::apicolypse::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::apicolypse::k_name.data() };
    MIN_TAGS{ airwindohhs::apicolypse::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    apicolypse_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(apicolypse_tilde);
