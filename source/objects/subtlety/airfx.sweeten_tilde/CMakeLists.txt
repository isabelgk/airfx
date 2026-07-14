set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.sweeten_tilde) # output bundle: airfx.sweeten~.mxo (_tilde->~)

target_sources(airfx.sweeten_tilde
    PRIVATE
        airfx.sweeten_tilde.cpp)

target_include_directories(airfx.sweeten_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.sweeten_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
