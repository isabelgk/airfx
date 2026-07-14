set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.console8bussin_tilde) # output bundle: airfx.console8bussin~.mxo (_tilde->~)

target_sources(airfx.console8bussin_tilde
    PRIVATE
        airfx.console8bussin_tilde.cpp)

target_include_directories(airfx.console8bussin_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.console8bussin_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
