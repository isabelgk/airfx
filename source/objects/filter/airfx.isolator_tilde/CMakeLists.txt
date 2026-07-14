set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.isolator_tilde) # output bundle: airfx.isolator~.mxo (_tilde->~)

target_sources(airfx.isolator_tilde
    PRIVATE
        airfx.isolator_tilde.cpp)

target_include_directories(airfx.isolator_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.isolator_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
