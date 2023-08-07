file(REMOVE_RECURSE
  "librbc.a"
  "librbc.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/rbc.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
