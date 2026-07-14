set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.ulawdecode_tilde) # output bundle: airfx.ulawdecode~.mxo (_tilde->~)

target_sources(airfx.ulawdecode_tilde
    PRIVATE
        airfx.ulawdecode_tilde.cpp)

target_include_directories(airfx.ulawdecode_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.ulawdecode_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
