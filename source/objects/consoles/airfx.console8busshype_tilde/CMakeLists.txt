set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.console8busshype_tilde) # output bundle: airfx.console8busshype~.mxo (_tilde->~)

target_sources(airfx.console8busshype_tilde
    PRIVATE
        airfx.console8busshype_tilde.cpp)

target_include_directories(airfx.console8busshype_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.console8busshype_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
