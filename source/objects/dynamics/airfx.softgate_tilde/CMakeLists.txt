set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.softgate_tilde) # output bundle: airfx.softgate~.mxo (_tilde->~)

target_sources(airfx.softgate_tilde
    PRIVATE
        airfx.softgate_tilde.cpp)

target_include_directories(airfx.softgate_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.softgate_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
