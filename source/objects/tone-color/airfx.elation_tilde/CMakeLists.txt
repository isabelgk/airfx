set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.elation_tilde) # output bundle: airfx.elation~.mxo (_tilde->~)

target_sources(airfx.elation_tilde
    PRIVATE
        airfx.elation_tilde.cpp)

target_include_directories(airfx.elation_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.elation_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
