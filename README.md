# emp-zk-tutorial

## install instructions:
1. open new folder in VSCode, `Terminal -> New Terminal`
2. `git clone https://github.com/olea-digitalis/emp-zk-tutorial.git` then `cd emp-zk-tutorial`
3. `wget https://raw.githubusercontent.com/emp-toolkit/emp-readme/master/scripts/install.py` (source: https://github.com/emp-toolkit/emp-zk )
4. `python[3] install.py --deps --tool --ot --zk`
5. `mkdir data`


## Compile & Run Example File
To compile:
- `cmake . && make`

To run:
- `./run bin/test_basic_zk`
