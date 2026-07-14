set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.suzan_tilde) # output bundle: airfx.suzan~.mxo (_tilde->~)

target_sources(airfx.suzan_tilde
    PRIVATE
        airfx.suzan_tilde.cpp)

target_include_directories(airfx.suzan_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.suzan_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
