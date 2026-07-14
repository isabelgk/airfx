set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.dubly3_tilde) # output bundle: airfx.dubly3~.mxo (_tilde->~)

target_sources(airfx.dubly3_tilde
    PRIVATE
        airfx.dubly3_tilde.cpp)

target_include_directories(airfx.dubly3_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.dubly3_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
