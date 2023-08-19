cmake_minimum_required(VERSION 3.16)

file(GLOB SRC
	mediaconfig.cxx
)

add_executable(MediaConfig WIN32 ${SRC})
target_link_libraries(MediaConfig
	PRIVATE nlohmann_json
	PRIVATE winui
)
target_compile_features(MediaConfig PRIVATE cxx_std_17)