set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.dubplate2_tilde) # output bundle: airfx.dubplate2~.mxo (_tilde->~)

target_sources(airfx.dubplate2_tilde
    PRIVATE
        airfx.dubplate2_tilde.cpp)

target_include_directories(airfx.dubplate2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.dubplate2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
