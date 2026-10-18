set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.purestconsole4channel_tilde) # output bundle: airfx.purestconsole4channel~.mxo (_tilde->~)

target_sources(airfx.purestconsole4channel_tilde
    PRIVATE
        airfx.purestconsole4channel_tilde.cpp)

target_include_directories(airfx.purestconsole4channel_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.purestconsole4channel_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
