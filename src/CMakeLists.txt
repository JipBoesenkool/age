#core
add_subdirectory(os)
add_subdirectory(core)
add_subdirectory(glfw)

add_subdirectory(memory)
add_subdirectory(reflection)

#patterns
add_subdirectory(pattern/pubsub)
add_subdirectory(pattern/message)
add_subdirectory(pattern/event)

add_subdirectory(ecs)

#build the shared libs
add_subdirectory(renderer/ogl_renderer)
