file(REMOVE_RECURSE
  "librbc-nist.a"
  "librbc-nist.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/rbc-nist.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
