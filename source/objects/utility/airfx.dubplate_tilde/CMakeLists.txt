set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.dubplate_tilde) # output bundle: airfx.dubplate~.mxo (_tilde->~)

target_sources(airfx.dubplate_tilde
    PRIVATE
        airfx.dubplate_tilde.cpp)

target_include_directories(airfx.dubplate_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.dubplate_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
