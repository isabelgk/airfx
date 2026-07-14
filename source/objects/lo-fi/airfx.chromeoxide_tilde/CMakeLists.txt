set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.chromeoxide_tilde) # output bundle: airfx.chromeoxide~.mxo (_tilde->~)

target_sources(airfx.chromeoxide_tilde
    PRIVATE
        airfx.chromeoxide_tilde.cpp)

target_include_directories(airfx.chromeoxide_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.chromeoxide_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
