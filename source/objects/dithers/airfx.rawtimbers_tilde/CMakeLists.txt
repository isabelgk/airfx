set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.rawtimbers_tilde) # output bundle: airfx.rawtimbers~.mxo (_tilde->~)

target_sources(airfx.rawtimbers_tilde
    PRIVATE
        airfx.rawtimbers_tilde.cpp)

target_include_directories(airfx.rawtimbers_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.rawtimbers_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
