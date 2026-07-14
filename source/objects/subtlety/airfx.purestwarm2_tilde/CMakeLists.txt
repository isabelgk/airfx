set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.purestwarm2_tilde) # output bundle: airfx.purestwarm2~.mxo (_tilde->~)

target_sources(airfx.purestwarm2_tilde
    PRIVATE
        airfx.purestwarm2_tilde.cpp)

target_include_directories(airfx.purestwarm2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.purestwarm2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
