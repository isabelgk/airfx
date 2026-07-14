set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.reseq2_tilde) # output bundle: airfx.reseq2~.mxo (_tilde->~)

target_sources(airfx.reseq2_tilde
    PRIVATE
        airfx.reseq2_tilde.cpp)

target_include_directories(airfx.reseq2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.reseq2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
