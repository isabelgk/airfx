set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.interstage_tilde) # output bundle: airfx.interstage~.mxo (_tilde->~)

target_sources(airfx.interstage_tilde
    PRIVATE
        airfx.interstage_tilde.cpp)

target_include_directories(airfx.interstage_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.interstage_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
