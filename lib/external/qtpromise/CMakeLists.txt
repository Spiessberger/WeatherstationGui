include(FetchContent)

# Prefer a qtpromise provided by the system (any version); fall back to fetching
# the pinned one if find_package() comes up empty. Upstream ships no install
# rules, so a system copy only exists if a distribution packages one - hence
# both spellings of the package name.
FetchContent_Declare(qtpromise
  GIT_REPOSITORY https://github.com/simonbrunel/qtpromise.git
  GIT_TAG v0.7.0
  GIT_SHALLOW true
  FIND_PACKAGE_ARGS
)

FetchContent_MakeAvailable(qtpromise)
