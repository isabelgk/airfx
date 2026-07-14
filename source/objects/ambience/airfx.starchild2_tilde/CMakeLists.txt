set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.starchild2_tilde) # output bundle: airfx.starchild2~.mxo (_tilde->~)

target_sources(airfx.starchild2_tilde
    PRIVATE
        airfx.starchild2_tilde.cpp)

target_include_directories(airfx.starchild2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.starchild2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
