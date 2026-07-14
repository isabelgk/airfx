set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.reseq_tilde) # output bundle: airfx.reseq~.mxo (_tilde->~)

target_sources(airfx.reseq_tilde
    PRIVATE
        airfx.reseq_tilde.cpp)

target_include_directories(airfx.reseq_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.reseq_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
