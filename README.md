# emp-zk-tutorial

## Install Instructions

##### Mac:
- download and install xcode https://apps.apple.com/us/app/xcode/id497799835?mt=12
- then follow 1. below

##### Windows:
- install WSL first, then start from 1. below *inside* WSL

---------

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
