add_library(
        PID
        SHARED
        pid.cpp
        parser.cpp
        learner.cpp
        uws_utils.cpp
        error_function.cpp
        controller.cpp
)

target_link_libraries(PID uWS z ssl uv)