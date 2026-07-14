set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.pyewacket_tilde) # output bundle: airfx.pyewacket~.mxo (_tilde->~)

target_sources(airfx.pyewacket_tilde
    PRIVATE
        airfx.pyewacket_tilde.cpp)

target_include_directories(airfx.pyewacket_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.pyewacket_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
