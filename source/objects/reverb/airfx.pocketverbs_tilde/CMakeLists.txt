set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.pocketverbs_tilde) # output bundle: airfx.pocketverbs~.mxo (_tilde->~)

target_sources(airfx.pocketverbs_tilde
    PRIVATE
        airfx.pocketverbs_tilde.cpp)

target_include_directories(airfx.pocketverbs_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.pocketverbs_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
