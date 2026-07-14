set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.dubsub2_tilde) # output bundle: airfx.dubsub2~.mxo (_tilde->~)

target_sources(airfx.dubsub2_tilde
    PRIVATE
        airfx.dubsub2_tilde.cpp)

target_include_directories(airfx.dubsub2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.dubsub2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
