set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.chimeyguitar2_tilde) # output bundle: airfx.chimeyguitar2~.mxo (_tilde->~)

target_sources(airfx.chimeyguitar2_tilde
    PRIVATE
        airfx.chimeyguitar2_tilde.cpp)

target_include_directories(airfx.chimeyguitar2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.chimeyguitar2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
