set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.consolemcchannel_tilde) # output bundle: airfx.consolemcchannel~.mxo (_tilde->~)

target_sources(airfx.consolemcchannel_tilde
    PRIVATE
        airfx.consolemcchannel_tilde.cpp)

target_include_directories(airfx.consolemcchannel_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.consolemcchannel_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
