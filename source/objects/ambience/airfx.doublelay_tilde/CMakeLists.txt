set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.doublelay_tilde) # output bundle: airfx.doublelay~.mxo (_tilde->~)

target_sources(airfx.doublelay_tilde
    PRIVATE
        airfx.doublelay_tilde.cpp)

target_include_directories(airfx.doublelay_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.doublelay_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
