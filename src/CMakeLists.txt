add_library(oakd_webcam 
    dai_controller.cpp 
    dai_controller.hpp
)

target_include_directories(oakd_webcam PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(oakd_webcam PUBLIC depthai::core)
