set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.pitchnasty_tilde) # output bundle: airfx.pitchnasty~.mxo (_tilde->~)

target_sources(airfx.pitchnasty_tilde
    PRIVATE
        airfx.pitchnasty_tilde.cpp)

target_include_directories(airfx.pitchnasty_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.pitchnasty_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
