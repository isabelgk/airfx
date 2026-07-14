set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.dubly_tilde) # output bundle: airfx.dubly~.mxo (_tilde->~)

target_sources(airfx.dubly_tilde
    PRIVATE
        airfx.dubly_tilde.cpp)

target_include_directories(airfx.dubly_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.dubly_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
