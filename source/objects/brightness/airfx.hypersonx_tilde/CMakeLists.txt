set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.hypersonx_tilde) # output bundle: airfx.hypersonx~.mxo (_tilde->~)

target_sources(airfx.hypersonx_tilde
    PRIVATE
        airfx.hypersonx_tilde.cpp)

target_include_directories(airfx.hypersonx_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.hypersonx_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
