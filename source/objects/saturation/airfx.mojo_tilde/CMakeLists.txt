set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.mojo_tilde) # output bundle: airfx.mojo~.mxo (_tilde->~)

target_sources(airfx.mojo_tilde
    PRIVATE
        airfx.mojo_tilde.cpp)

target_include_directories(airfx.mojo_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.mojo_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
