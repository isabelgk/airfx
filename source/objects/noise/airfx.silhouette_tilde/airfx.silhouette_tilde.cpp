#include "c74_min.h"
#include "airfx.hpp"
#include "noise/silhouette.hpp"

using namespace c74::min;

class silhouette_tilde : public airfx<silhouette_tilde, airwindohhs::silhouette::Silhouette<double>>
{
    atom m_about_text = symbol{ airwindohhs::silhouette::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::silhouette::k_name.data() };
    MIN_TAGS{ airwindohhs::silhouette::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    silhouette_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(silhouette_tilde);
