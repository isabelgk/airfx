set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.fracture2_tilde) # output bundle: airfx.fracture2~.mxo (_tilde->~)

target_sources(airfx.fracture2_tilde
    PRIVATE
        airfx.fracture2_tilde.cpp)

target_include_directories(airfx.fracture2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.fracture2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
