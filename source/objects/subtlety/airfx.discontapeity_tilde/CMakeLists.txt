set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.discontapeity_tilde) # output bundle: airfx.discontapeity~.mxo (_tilde->~)

target_sources(airfx.discontapeity_tilde
    PRIVATE
        airfx.discontapeity_tilde.cpp)

target_include_directories(airfx.discontapeity_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.discontapeity_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
