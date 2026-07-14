set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.tubedesk_tilde) # output bundle: airfx.tubedesk~.mxo (_tilde->~)

target_sources(airfx.tubedesk_tilde
    PRIVATE
        airfx.tubedesk_tilde.cpp)

target_include_directories(airfx.tubedesk_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.tubedesk_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
