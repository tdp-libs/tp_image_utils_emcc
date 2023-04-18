set -xe

rm -rf libjpeg-turbo
git clone https://github.com/libjpeg-turbo/libjpeg-turbo.git

rm -rf build
rm -rf install

mkdir build
mkdir install

cd build
emcmake cmake -G"Unix Makefiles" \
 -DCMAKE_BUILD_TYPE=Release \
 -DWITH_SIMD=0 \
 -DENABLE_SHARED=0 \
 -DWITH_TURBOJPEG=0 \
 -DCMAKE_INSTALL_PREFIX=`realpath ../install` \
 ../libjpeg-turbo

make -j20 install VERBOSE=1

