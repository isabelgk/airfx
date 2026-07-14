set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.bigamp_tilde) # output bundle: airfx.bigamp~.mxo (_tilde->~)

target_sources(airfx.bigamp_tilde
    PRIVATE
        airfx.bigamp_tilde.cpp)

target_include_directories(airfx.bigamp_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.bigamp_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
