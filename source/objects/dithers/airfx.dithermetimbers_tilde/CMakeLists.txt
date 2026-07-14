set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.dithermetimbers_tilde) # output bundle: airfx.dithermetimbers~.mxo (_tilde->~)

target_sources(airfx.dithermetimbers_tilde
    PRIVATE
        airfx.dithermetimbers_tilde.cpp)

target_include_directories(airfx.dithermetimbers_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.dithermetimbers_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
