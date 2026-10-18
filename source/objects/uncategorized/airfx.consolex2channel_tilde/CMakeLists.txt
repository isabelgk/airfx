set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.consolex2channel_tilde) # output bundle: airfx.consolex2channel~.mxo (_tilde->~)

target_sources(airfx.consolex2channel_tilde
    PRIVATE
        airfx.consolex2channel_tilde.cpp)

target_include_directories(airfx.consolex2channel_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.consolex2channel_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
