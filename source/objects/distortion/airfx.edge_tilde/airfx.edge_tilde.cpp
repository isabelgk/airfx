#include "c74_min.h"
#include "airfx.hpp"
#include "distortion/edge.hpp"

using namespace c74::min;

class edge_tilde : public airfx<edge_tilde, airwindohhs::edge::Edge<double>>
{
    atom m_about_text = symbol{ airwindohhs::edge::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::edge::k_name.data() };
    MIN_TAGS{ airwindohhs::edge::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    edge_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(edge_tilde);
