

rmdir /S /Q build 2> nul
mkdir build
cd build
cmake -A x64 -DCMAKE_BUILD_TYPE=relwithdebinfo -DBUILD_SHARED_LIBS=ON ..
cmake --build . --config relwithdebinfo -- /m:%NUMBER_OF_PROCESSORS%
echo "cd build && ctest -C relwithdebinfo --output-on-failure --output-junit report.xml"
cd ..

rem pause