set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.compresaturator_tilde) # output bundle: airfx.compresaturator~.mxo (_tilde->~)

target_sources(airfx.compresaturator_tilde
    PRIVATE
        airfx.compresaturator_tilde.cpp)

target_include_directories(airfx.compresaturator_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.compresaturator_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
