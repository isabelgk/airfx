set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.purestdrive_tilde) # output bundle: airfx.purestdrive~.mxo (_tilde->~)

target_sources(airfx.purestdrive_tilde
    PRIVATE
        airfx.purestdrive_tilde.cpp)

target_include_directories(airfx.purestdrive_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.purestdrive_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
