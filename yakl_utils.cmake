

function(yakl_get_lang_from_list files lang langfiles)
  set(lang_files_loc "")
  foreach(file ${files})
    get_source_file_property(lang_loc ${file} LANGUAGE)
    if ("${lang_loc}" STREQUAL "${lang}")
      list(APPEND lang_files_loc "${file}")
    endif()
  endforeach()
  set(${langfiles} "${lang_files_loc}" PARENT_SCOPE)
endfunction()



macro(yakl_process_cxx_source_files files)
  add_compile_definitions ( YAKL_ARCH_${YAKL_ARCH} )

  if ("${YAKL_ARCH}" STREQUAL "CUDA")
    set_source_files_properties(${files} PROPERTIES LANGUAGE CUDA)
    set(YAKL_COMPILER_FLAGS "--expt-extended-lambda --expt-relaxed-constexpr -Wno-deprecated-gpu-targets -std=c++17 ${YAKL_CUDA_FLAGS}")
  elseif ("${YAKL_ARCH}" STREQUAL "HIP")
    set(YAKL_COMPILER_FLAGS "${YAKL_HIP_FLAGS}")
  elseif ("${YAKL_ARCH}" STREQUAL "SYCL")
    if (YAKL_SYCL_USE_BBFFT)
      add_compile_definitions(YAKL_SYCL_BBFFT)
      if (YAKL_SYCL_BBFFT_USE_AOT)
        add_compile_definitions(YAKL_SYCL_BBFFT_AOT)
      endif()
    endif()
    set(YAKL_COMPILER_FLAGS "${YAKL_SYCL_FLAGS}")
  elseif ("${YAKL_ARCH}" STREQUAL "OPENMP45")
    set(YAKL_COMPILER_FLAGS "${YAKL_OPENMP45_FLAGS}")
  elseif ("${YAKL_ARCH}" STREQUAL "OPENMP")
    set(YAKL_COMPILER_FLAGS "${YAKL_OPENMP_FLAGS}")
  else()
    set(YAKL_COMPILER_FLAGS "${YAKL_CXX_FLAGS}")
  endif()

  set_source_files_properties(${files} PROPERTIES COMPILE_FLAGS "${YAKL_COMPILER_FLAGS}")
  set_source_files_properties(${files} PROPERTIES CXX_STANDARD 17)
endmacro(yakl_process_cxx_source_files)




macro(yakl_process_target tname)
  get_target_property(files ${tname} SOURCES)
  yakl_get_lang_from_list("${files}" "CXX" cxxfiles)

  yakl_process_cxx_source_files("${cxxfiles}")

  set_property(TARGET ${tname} PROPERTY CXX_STANDARD 17)

  target_link_libraries(${tname} yakl)
endmacro(yakl_process_target)



