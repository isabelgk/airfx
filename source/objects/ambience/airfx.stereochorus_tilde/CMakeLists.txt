set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.stereochorus_tilde) # output bundle: airfx.stereochorus~.mxo (_tilde->~)

target_sources(airfx.stereochorus_tilde
    PRIVATE
        airfx.stereochorus_tilde.cpp)

target_include_directories(airfx.stereochorus_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.stereochorus_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
