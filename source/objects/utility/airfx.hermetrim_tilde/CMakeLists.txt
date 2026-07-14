set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.hermetrim_tilde) # output bundle: airfx.hermetrim~.mxo (_tilde->~)

target_sources(airfx.hermetrim_tilde
    PRIVATE
        airfx.hermetrim_tilde.cpp)

target_include_directories(airfx.hermetrim_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.hermetrim_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
