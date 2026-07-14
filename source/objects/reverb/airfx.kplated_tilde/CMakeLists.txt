set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.kplated_tilde) # output bundle: airfx.kplated~.mxo (_tilde->~)

target_sources(airfx.kplated_tilde
    PRIVATE
        airfx.kplated_tilde.cpp)

target_include_directories(airfx.kplated_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.kplated_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
