set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.totape6_tilde) # output bundle: airfx.totape6~.mxo (_tilde->~)

target_sources(airfx.totape6_tilde
    PRIVATE
        airfx.totape6_tilde.cpp)

target_include_directories(airfx.totape6_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.totape6_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
