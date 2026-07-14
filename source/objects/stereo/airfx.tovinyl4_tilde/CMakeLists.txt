set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.tovinyl4_tilde) # output bundle: airfx.tovinyl4~.mxo (_tilde->~)

target_sources(airfx.tovinyl4_tilde
    PRIVATE
        airfx.tovinyl4_tilde.cpp)

target_include_directories(airfx.tovinyl4_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.tovinyl4_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
