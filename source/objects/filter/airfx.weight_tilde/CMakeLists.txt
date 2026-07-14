set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.weight_tilde) # output bundle: airfx.weight~.mxo (_tilde->~)

target_sources(airfx.weight_tilde
    PRIVATE
        airfx.weight_tilde.cpp)

target_include_directories(airfx.weight_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.weight_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
