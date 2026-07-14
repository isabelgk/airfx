set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.zoutputstage_tilde) # output bundle: airfx.zoutputstage~.mxo (_tilde->~)

target_sources(airfx.zoutputstage_tilde
    PRIVATE
        airfx.zoutputstage_tilde.cpp)

target_include_directories(airfx.zoutputstage_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.zoutputstage_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
