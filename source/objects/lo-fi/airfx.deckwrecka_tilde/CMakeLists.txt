set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.deckwrecka_tilde) # output bundle: airfx.deckwrecka~.mxo (_tilde->~)

target_sources(airfx.deckwrecka_tilde
    PRIVATE
        airfx.deckwrecka_tilde.cpp)

target_include_directories(airfx.deckwrecka_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.deckwrecka_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
