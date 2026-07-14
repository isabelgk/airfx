set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.totape5_tilde) # output bundle: airfx.totape5~.mxo (_tilde->~)

target_sources(airfx.totape5_tilde
    PRIVATE
        airfx.totape5_tilde.cpp)

target_include_directories(airfx.totape5_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.totape5_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
