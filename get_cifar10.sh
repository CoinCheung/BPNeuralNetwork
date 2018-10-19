
mkdir -p data
cd data
wget -c https://www.cs.toronto.edu/~kriz/cifar-10-binary.tar.gz
tar -zxvf cifar-10-binary.tar.gz

mkdir -p cifar_images/train/
mkdir -p cifar_images/test/
