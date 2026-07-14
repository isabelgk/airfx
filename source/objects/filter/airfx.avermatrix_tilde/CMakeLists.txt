set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.avermatrix_tilde) # output bundle: airfx.avermatrix~.mxo (_tilde->~)

target_sources(airfx.avermatrix_tilde
    PRIVATE
        airfx.avermatrix_tilde.cpp)

target_include_directories(airfx.avermatrix_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.avermatrix_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
