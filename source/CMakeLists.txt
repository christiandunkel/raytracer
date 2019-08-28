add_executable(raytracer raytracer.cpp)

target_link_libraries(raytracer ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(raytracer glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS raytracer DESTINATION .)

# Build tests
add_executable(tests
  tests.cpp
  ../framework/material.cpp
  ../framework/shape.cpp
  ../framework/sphere.cpp
  ../framework/box.cpp
  ../framework/triangle.cpp
  ../framework/sdfManager.cpp
  ../framework/scene.cpp
  ../framework/renderer.cpp
  ../framework/pixel.cpp
  ../framework/ppmwriter.cpp
  ../framework/camera.cpp
  ../framework/ray.cpp
  ../framework/hitpoint.cpp
  ../framework/composite.cpp
  ../framework/cone.cpp
  ../framework/cylinder.cpp
  ../framework/animation.cpp
)
target_link_libraries(tests
  ${GLFW_LIBRARIES}
  )
