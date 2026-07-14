set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.dubsub_tilde) # output bundle: airfx.dubsub~.mxo (_tilde->~)

target_sources(airfx.dubsub_tilde
    PRIVATE
        airfx.dubsub_tilde.cpp)

target_include_directories(airfx.dubsub_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.dubsub_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
