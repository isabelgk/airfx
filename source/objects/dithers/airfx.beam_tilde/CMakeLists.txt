set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.beam_tilde) # output bundle: airfx.beam~.mxo (_tilde->~)

target_sources(airfx.beam_tilde
    PRIVATE
        airfx.beam_tilde.cpp)

target_include_directories(airfx.beam_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.beam_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
