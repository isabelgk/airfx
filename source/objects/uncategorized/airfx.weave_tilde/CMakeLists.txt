set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.weave_tilde) # output bundle: airfx.weave~.mxo (_tilde->~)

target_sources(airfx.weave_tilde
    PRIVATE
        airfx.weave_tilde.cpp)

target_include_directories(airfx.weave_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.weave_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
