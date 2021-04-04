#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "IMAGE_PROCESSOR_LIB::ImageProcessor" for configuration ""
set_property(TARGET IMAGE_PROCESSOR_LIB::ImageProcessor APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(IMAGE_PROCESSOR_LIB::ImageProcessor PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libimageProcessor.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS IMAGE_PROCESSOR_LIB::ImageProcessor )
list(APPEND _IMPORT_CHECK_FILES_FOR_IMAGE_PROCESSOR_LIB::ImageProcessor "${_IMPORT_PREFIX}/lib/libimageProcessor.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
