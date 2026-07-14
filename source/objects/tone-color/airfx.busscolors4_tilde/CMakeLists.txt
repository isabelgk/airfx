set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.busscolors4_tilde) # output bundle: airfx.busscolors4~.mxo (_tilde->~)

target_sources(airfx.busscolors4_tilde
    PRIVATE
        airfx.busscolors4_tilde.cpp)

target_include_directories(airfx.busscolors4_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.busscolors4_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
