set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.transdesk_tilde) # output bundle: airfx.transdesk~.mxo (_tilde->~)

target_sources(airfx.transdesk_tilde
    PRIVATE
        airfx.transdesk_tilde.cpp)

target_include_directories(airfx.transdesk_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.transdesk_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
