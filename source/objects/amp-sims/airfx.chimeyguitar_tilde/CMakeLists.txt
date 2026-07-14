set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.chimeyguitar_tilde) # output bundle: airfx.chimeyguitar~.mxo (_tilde->~)

target_sources(airfx.chimeyguitar_tilde
    PRIVATE
        airfx.chimeyguitar_tilde.cpp)

target_include_directories(airfx.chimeyguitar_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.chimeyguitar_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
