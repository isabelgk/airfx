set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.kguitarhall_tilde) # output bundle: airfx.kguitarhall~.mxo (_tilde->~)

target_sources(airfx.kguitarhall_tilde
    PRIVATE
        airfx.kguitarhall_tilde.cpp)

target_include_directories(airfx.kguitarhall_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.kguitarhall_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
