include(FetchContent)

# Adding pugixml library
FetchContent_Declare(
  pugixml
  GIT_REPOSITORY https://github.com/zeux/pugixml
  GIT_TAG v1.14
  GIT_SHALLOW TRUE
  SYSTEM)
FetchContent_MakeAvailable(pugixml)
