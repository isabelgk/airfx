set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.pop3_tilde) # output bundle: airfx.pop3~.mxo (_tilde->~)

target_sources(airfx.pop3_tilde
    PRIVATE
        airfx.pop3_tilde.cpp)

target_include_directories(airfx.pop3_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.pop3_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
