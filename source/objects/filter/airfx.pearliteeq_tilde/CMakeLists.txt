set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.pearliteeq_tilde) # output bundle: airfx.pearliteeq~.mxo (_tilde->~)

target_sources(airfx.pearliteeq_tilde
    PRIVATE
        airfx.pearliteeq_tilde.cpp)

target_include_directories(airfx.pearliteeq_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.pearliteeq_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
