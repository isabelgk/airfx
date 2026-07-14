set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.wolfbot_tilde) # output bundle: airfx.wolfbot~.mxo (_tilde->~)

target_sources(airfx.wolfbot_tilde
    PRIVATE
        airfx.wolfbot_tilde.cpp)

target_include_directories(airfx.wolfbot_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.wolfbot_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
