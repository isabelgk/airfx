#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/podcast.hpp"

using namespace c74::min;

class podcast_tilde : public airfx<podcast_tilde, airwindohhs::podcast::Podcast<double>>
{
    atom m_about_text = symbol{ airwindohhs::podcast::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::podcast::k_name.data() };
    MIN_TAGS{ airwindohhs::podcast::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    podcast_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(podcast_tilde);
