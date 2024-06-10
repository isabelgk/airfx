#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/podcastdeluxe.hpp"

using namespace c74::min;

class podcastdeluxe_tilde : public airfx<podcastdeluxe_tilde, airwindohhs::podcastdeluxe::PodcastDeluxe<double>>
{
    atom m_about_text = symbol{ airwindohhs::podcastdeluxe::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::podcastdeluxe::k_name.data() };
    MIN_TAGS{ airwindohhs::podcastdeluxe::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    podcastdeluxe_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(podcastdeluxe_tilde);
