set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.purestwarm3_tilde) # output bundle: airfx.purestwarm3~.mxo (_tilde->~)

target_sources(airfx.purestwarm3_tilde
    PRIVATE
        airfx.purestwarm3_tilde.cpp)

target_include_directories(airfx.purestwarm3_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.purestwarm3_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
