include(FetchContent)

FetchContent_Declare(
  glaze
  GIT_REPOSITORY https://github.com/stephenberry/glaze.git
  GIT_TAG v7.3.3
  GIT_SHALLOW TRUE
  FIND_PACKAGE_ARGS GLOBAL
)

FetchContent_MakeAvailable(glaze)
