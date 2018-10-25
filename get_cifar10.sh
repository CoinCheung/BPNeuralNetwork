
# download and uncompress dataset
mkdir -p data
cd data
wget -c https://www.cs.toronto.edu/~kriz/cifar-10-binary.tar.gz
tar -zxvf cifar-10-binary.tar.gz

# build and decode images
mkdir -p cifar_images/train/ cifar_images/test/ cifar_dbs/ build/
cd build
cmake .. && make
./main ..
cd ..
rm -rf build

