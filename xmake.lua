set_project("xmake-example-qt")
set_languages("c++17")
add_rules("mode.debug", "mode.release")
-- cmake packages
add_requires("cmake::LibXml2", {system = true})
add_requires("cmake::OpenCV", {system = true})
-- conan packages
-- add_requires("conan::xpack 1.0.2", {alias = "xpack",debug = true})
-- add_requires("conan::sqlite_orm 1.7.1", {alias = "sqlite_orm",debug = true})

-- native xmake packages
add_requires("tbox master", {debug = true})
add_requires("openssl", {alias = "openssl",
    configs = {options = "OpenSSL:shared=True"}})
add_requires("sqlite3 3.39.0","yaml-cpp 0.7.0","fmt 9.1.0","coost 3.0.0","cppzmq 4.8.1","toml++ 3.2.0","cpr 1.8.3","concurrentqueue","xtensor","xtl","xtensor-blas") 


add_rules("mode.debug", "mode.release")

target("test")
    set_kind("static")
    add_files("src/test.cpp")
    -- add_packages("pcre2", {public = true})

target("qt")
    add_deps("test")
    add_files("src/*.cpp")
    add_files("src/qml.qrc")
    add_includedirs("include")
    add_headerfiles("include/*.h","include/*.hpp")
    add_rules("qt.quickapp")

    
    add_packages("cmake::LibXml2","cmake::OpenCV")
    -- add_packages("conan::xpack","conan::sqlite_orm")  
    add_packages("tbox","yaml-cpp","fmt","coost","cppzmq","sqlite3")

    add_defines("LOGURU_WITH_STREAMS","LOGURU_USE_FMTLIB")

