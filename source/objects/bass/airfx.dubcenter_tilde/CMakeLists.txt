set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.dubcenter_tilde) # output bundle: airfx.dubcenter~.mxo (_tilde->~)

target_sources(airfx.dubcenter_tilde
    PRIVATE
        airfx.dubcenter_tilde.cpp)

target_include_directories(airfx.dubcenter_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.dubcenter_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
