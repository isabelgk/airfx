set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.purestconsole2channel_tilde) # output bundle: airfx.purestconsole2channel~.mxo (_tilde->~)

target_sources(airfx.purestconsole2channel_tilde
    PRIVATE
        airfx.purestconsole2channel_tilde.cpp)

target_include_directories(airfx.purestconsole2channel_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.purestconsole2channel_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
