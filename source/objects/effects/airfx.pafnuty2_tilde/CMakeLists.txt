set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.pafnuty2_tilde) # output bundle: airfx.pafnuty2~.mxo (_tilde->~)

target_sources(airfx.pafnuty2_tilde
    PRIVATE
        airfx.pafnuty2_tilde.cpp)

target_include_directories(airfx.pafnuty2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.pafnuty2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
