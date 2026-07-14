set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.doublepaul_tilde) # output bundle: airfx.doublepaul~.mxo (_tilde->~)

target_sources(airfx.doublepaul_tilde
    PRIVATE
        airfx.doublepaul_tilde.cpp)

target_include_directories(airfx.doublepaul_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.doublepaul_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
