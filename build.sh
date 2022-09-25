PROJECT_DIR="."
BUILD_DIR="./build"

echo "PROJECT_DIR: ${PROJECT_DIR}"
echo "BUILD_DIR: ${BUILD_DIR}"

echo "Cleaning BUILD_DIR: ${BUILD_DIR}"
rm -rf "${BUILD_DIR}"

echo "Building to BUILD_DIR: ${BUILD_DIR}"
cmake -S "${PROJECT_DIR}" -B "${BUILD_DIR}"
cmake --build ${BUILD_DIR}



