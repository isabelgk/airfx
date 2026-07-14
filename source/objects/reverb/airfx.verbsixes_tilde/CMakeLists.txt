set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.verbsixes_tilde) # output bundle: airfx.verbsixes~.mxo (_tilde->~)

target_sources(airfx.verbsixes_tilde
    PRIVATE
        airfx.verbsixes_tilde.cpp)

target_include_directories(airfx.verbsixes_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.verbsixes_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
