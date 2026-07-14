set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.facet_tilde) # output bundle: airfx.facet~.mxo (_tilde->~)

target_sources(airfx.facet_tilde
    PRIVATE
        airfx.facet_tilde.cpp)

target_include_directories(airfx.facet_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.facet_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
