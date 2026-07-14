set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.paulwide_tilde) # output bundle: airfx.paulwide~.mxo (_tilde->~)

target_sources(airfx.paulwide_tilde
    PRIVATE
        airfx.paulwide_tilde.cpp)

target_include_directories(airfx.paulwide_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.paulwide_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
