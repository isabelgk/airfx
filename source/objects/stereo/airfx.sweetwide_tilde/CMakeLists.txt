set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.sweetwide_tilde) # output bundle: airfx.sweetwide~.mxo (_tilde->~)

target_sources(airfx.sweetwide_tilde
    PRIVATE
        airfx.sweetwide_tilde.cpp)

target_include_directories(airfx.sweetwide_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.sweetwide_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
