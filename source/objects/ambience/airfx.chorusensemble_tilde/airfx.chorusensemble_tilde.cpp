#include "c74_min.h"
#include "airfx.hpp"
#include "ambience/chorusensemble.hpp"

using namespace c74::min;

class chorusensemble_tilde : public airfx<chorusensemble_tilde, airwindohhs::chorusensemble::ChorusEnsemble<double>>
{
    atom m_about_text = symbol{ airwindohhs::chorusensemble::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::chorusensemble::k_name.data() };
    MIN_TAGS{ airwindohhs::chorusensemble::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    chorusensemble_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(chorusensemble_tilde);
