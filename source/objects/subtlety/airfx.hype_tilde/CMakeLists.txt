set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.hype_tilde) # output bundle: airfx.hype~.mxo (_tilde->~)

target_sources(airfx.hype_tilde
    PRIVATE
        airfx.hype_tilde.cpp)

target_include_directories(airfx.hype_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.hype_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
