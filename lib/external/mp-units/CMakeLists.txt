include(FetchContent)

FetchContent_Declare(
  mp-units
  GIT_REPOSITORY https://github.com/mpusz/mp-units.git
  GIT_TAG v2.5.0
  SOURCE_SUBDIR src
)

set(MP_UNITS_API_CONTRACTS "NONE" CACHE STRING "" FORCE)
FetchContent_MakeAvailable(mp-units)
