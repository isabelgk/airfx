set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.dubly2_tilde) # output bundle: airfx.dubly2~.mxo (_tilde->~)

target_sources(airfx.dubly2_tilde
    PRIVATE
        airfx.dubly2_tilde.cpp)

target_include_directories(airfx.dubly2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.dubly2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
