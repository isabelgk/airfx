set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.totape9_tilde) # output bundle: airfx.totape9~.mxo (_tilde->~)

target_sources(airfx.totape9_tilde
    PRIVATE
        airfx.totape9_tilde.cpp)

target_include_directories(airfx.totape9_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.totape9_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
