set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.totape7_tilde) # output bundle: airfx.totape7~.mxo (_tilde->~)

target_sources(airfx.totape7_tilde
    PRIVATE
        airfx.totape7_tilde.cpp)

target_include_directories(airfx.totape7_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.totape7_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
