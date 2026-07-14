set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.fracture_tilde) # output bundle: airfx.fracture~.mxo (_tilde->~)

target_sources(airfx.fracture_tilde
    PRIVATE
        airfx.fracture_tilde.cpp)

target_include_directories(airfx.fracture_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.fracture_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
