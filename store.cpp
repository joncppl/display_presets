//
// Created by joncp on 6/8/2022.
//

#include "error.hpp"

#include <vector>
#include <fstream>
#include <Windows.h>


/// stores the current display configuration into the file with the path in argv[1]
int real_main(int argc, char* argv[])
{
  UINT32 num_path_array_elements {0};
  UINT32 num_mode_info_array_elements {0};

  LONG r = GetDisplayConfigBufferSizes(
    QDC_DATABASE_CURRENT,
    &num_path_array_elements,
    &num_mode_info_array_elements
  );

  if (r != ERROR_SUCCESS) {
    printf(" error [%ld] %s\n", r, error_string(r));
    return 1;
  }

  std::vector<DISPLAYCONFIG_PATH_INFO> path_array;
  path_array.resize(num_path_array_elements);

  std::vector<DISPLAYCONFIG_MODE_INFO> mode_info_array;
  mode_info_array.resize(num_mode_info_array_elements);

  DISPLAYCONFIG_TOPOLOGY_ID topology_id;

  r = QueryDisplayConfig(
    QDC_DATABASE_CURRENT,
    &num_path_array_elements,
    path_array.data(),
    &num_mode_info_array_elements,
    mode_info_array.data(),
    &topology_id
  );

  if (r != ERROR_SUCCESS) {
    printf(" error [%ld] %s\n", r, error_string(r));
    return 1;
  }

  printf("DisplayConfig Queried Successfully\n");

  const auto fpath = argc > 1 ? argv[1] : "preset";
  std::ofstream ofs(fpath, std::ios::binary | std::ios::out | std::ios::trunc);
  if (!ofs.is_open()) {
    fprintf(stderr, "Failed to open %s\n", fpath);
    return 1;
  }

  ofs.write((char*) &topology_id, sizeof(topology_id));
  ofs.write((char*) &num_path_array_elements, sizeof(num_path_array_elements));
  ofs.write((char*) path_array.data(), num_path_array_elements * sizeof(DISPLAYCONFIG_PATH_INFO));
  ofs.write((char*) &num_mode_info_array_elements, sizeof(num_mode_info_array_elements));
  ofs.write((char*) mode_info_array.data(), num_mode_info_array_elements * sizeof(DISPLAYCONFIG_MODE_INFO));

  printf("Wrote DisplayConfig to %s\n", fpath);

  return 0;
}

GUARD_MAIN(real_main)
