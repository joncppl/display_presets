//
// Created by joncp on 6/8/2022.
//

#include "error.hpp"

#include <vector>
#include <fstream>
#include <Windows.h>


/// loads a display config from the file with the path in argv[1] and applies it "temporarily"
int real_main(int argc, char* argv[])
{
  UINT32 num_path_array_elements {0};
  UINT32 num_mode_info_array_elements {0};
  std::vector<DISPLAYCONFIG_PATH_INFO> path_array;
  std::vector<DISPLAYCONFIG_MODE_INFO> mode_info_array;
  DISPLAYCONFIG_TOPOLOGY_ID topology_id;

  const auto fpath = argc > 1 ? argv[1] : "preset";
  std::ifstream ifs(fpath, std::ios::binary | std::ios::in);
  if (!ifs.is_open()) {
    fprintf(stderr, "Failed to open %s\n", fpath);
    return 1;
  }

  ifs.read((char*) &topology_id, sizeof(topology_id));
  ifs.read((char*) &num_path_array_elements, sizeof(num_path_array_elements));
  path_array.resize(num_path_array_elements);
  ifs.read((char*) path_array.data(), num_path_array_elements * sizeof(DISPLAYCONFIG_PATH_INFO));
  ifs.read((char*) &num_mode_info_array_elements, sizeof(num_mode_info_array_elements));
  mode_info_array.resize(num_mode_info_array_elements);
  ifs.read((char*) mode_info_array.data(), num_mode_info_array_elements * sizeof(DISPLAYCONFIG_MODE_INFO));

  LONG r = SetDisplayConfig(
    num_path_array_elements,
    path_array.data(),
    num_mode_info_array_elements,
    mode_info_array.data(),
    SDC_APPLY | SDC_USE_SUPPLIED_DISPLAY_CONFIG
  );

  if (r != ERROR_SUCCESS) {
    fprintf(stderr, "  error [%ld] %s\n", r, error_string(r));
    return 1;
  }

  printf("DisplayConfig loaded successfully\n");

  return 0;
}

GUARD_MAIN(real_main)
