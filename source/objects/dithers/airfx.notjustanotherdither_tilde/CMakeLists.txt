set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.notjustanotherdither_tilde) # output bundle: airfx.notjustanotherdither~.mxo (_tilde->~)

target_sources(airfx.notjustanotherdither_tilde
    PRIVATE
        airfx.notjustanotherdither_tilde.cpp)

target_include_directories(airfx.notjustanotherdither_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.notjustanotherdither_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
