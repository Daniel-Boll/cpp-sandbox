set_project("sandbox")
set_version("1.0.0")

set_languages("c++23")
add_rules("mode.debug", "mode.release")

local libs = {}

add_includedirs("include")
add_requires(table.unpack(libs))

target("sandbox-lib")
do
	set_kind("static")
	add_files("lib/**/*.cpp")
	add_packages(table.unpack(libs))
end

target("sandbox")
do
	set_kind("binary")
	add_files("src/main.cpp")
	add_packages(table.unpack(libs))
	add_deps("sandbox-lib")
end

add_installfiles("(include/**)", { prefixdir = "" })
