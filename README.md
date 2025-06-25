# emp-zk-tutorial

## Install Instructions

##### Mac:
- install wget: `brew install wget`
- install cmake: `brew install cmake`
- change everything in emp folder to Cmake requirement to version 3.5
script to update Cmake requirement:

```
for file in \
  ./emp-tool/CMakeLists.txt \
  ./emp-tool/test/CMakeLists.txt \
  ./CMakeLists.txt \
  ./test/CMakeLists.txt \
  ./emp-ot/CMakeLists.txt \
  ./emp-ot/test/CMakeLists.txt \
  ./emp-zk/CMakeLists.txt \
  ./emp-zk/test/CMakeLists.txt
do
  if [ -f "$file" ]; then
    sed -i '' '1s|.*|cmake_minimum_required(VERSION 3.5)|' "$file"
    echo "Updated: $file"
  else
    echo "File not found: $file"
  fi
done
```
- then follow 1. below

##### Windows:
- install WSL first, then start from 1. below *inside* WSL


1. open new folder in VSCode, `Terminal -> New Terminal`
2. `git clone https://github.com/olea-digitalis/emp-zk-tutorial.git` then `cd emp-zk-tutorial`
3. `wget https://raw.githubusercontent.com/emp-toolkit/emp-readme/master/scripts/install.py` (source: https://github.com/emp-toolkit/emp-zk )
5. `python[3] install.py --deps --tool --ot --zk`
6. `mkdir data`


## compile & run example file
To compile:
- `cmake . && make`

To run:
- `./run bin/test_basic_zk`
