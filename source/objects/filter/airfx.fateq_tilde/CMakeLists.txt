set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.fateq_tilde) # output bundle: airfx.fateq~.mxo (_tilde->~)

target_sources(airfx.fateq_tilde
    PRIVATE
        airfx.fateq_tilde.cpp)

target_include_directories(airfx.fateq_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.fateq_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
