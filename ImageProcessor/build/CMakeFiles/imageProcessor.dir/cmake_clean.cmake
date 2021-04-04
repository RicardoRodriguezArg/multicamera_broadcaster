file(REMOVE_RECURSE
  "libimageProcessor.a"
  "libimageProcessor.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/imageProcessor.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
