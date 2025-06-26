#include <emp-zk/emp-zk.h>
#include <emp-tool/emp-tool.h>
#include <iostream>

using namespace emp;
using namespace std;

int port, party;
const int threads = 1;


void hello_world_zk(BoolIO<NetIO> *ios[threads], int party) {
    setup_zk_bool<BoolIO<NetIO>>(ios, threads, party);

    Bit a(0, ALICE);
    Bit b(1, ALICE);

    cout << "hello world! revealing a^b: " << (a^b).reveal() << endl;

    bool cheat = finalize_zk_bool<BoolIO<NetIO>>();
    if (cheat)error("cheat!\n");
}


// write a protocol wherein Alice:
//     - commits to 4 hidden Bits
//     - proves to Bob the correctly computed parity of all 4 hidden Bits
// (the parity is 0 if there are an even number of 1s, and 1 otherwise)
void parity(BoolIO<NetIO> *ios[threads], int party) {
    setup_zk_bool<BoolIO<NetIO>>(ios, threads, party);
    Bit a(0,ALICE);
    Bit b(0,ALICE);
    Bit c(1,ALICE);
    Bit d(0,ALICE);

    // YOUR CODE HERE

    Bit parity(0,ALICE); // (replace or integrate into your code)
    cout << "parity: " << parity.reveal() << endl;

    bool cheat = finalize_zk_bool<BoolIO<NetIO>>();
    if (cheat)error("cheat!\n");
}
// q: how to compose operations?

// write a protocol wherein Alice: 
//     - commits to 4 hidden integers
//     - proves to Bob that all of them are non-negative, and below 10
//     - proves to Bob the correctly computed product of all 4 hidden integers
void threshold_and_sum(BoolIO<NetIO> *ios[threads], int party) {
    // YOUR CODE HERE
    // if you're getting unexpected segfaults, make sure you're calling setup_zk_bool() and finalize_zk_bool() !
}



// SUBROUTINES: these functions do not include setup and finalize operations -- instead we will call those operations in main()

// compute the euclidean distance between (a,b) and (x,y), and return it.
Float dist(Float a, Float b, Float x, Float y) {
    // YOUR CODE HERE
    Float ret(0, ALICE);
    return ret;
}

Integer example_vec_sum(vector<Integer> xs) {
    Integer ret(32, 0, ALICE);
    size_t sz = xs.size();
    for (int i=0; i<sz; ++i) {
        ret = ret + xs[i];
    }
    return ret;
}

// assuming xs is a vector containing 32 bit Integers, find the maximum value and return it
Integer max(vector<Integer> xs) {
    // YOUR CODE HERE
    Integer ret(32, -1, ALICE);
    return ret;
}


int main(int argc, char **argv) {
    parse_party_and_port(argv, &party, &port);
    BoolIO<NetIO> *ios[threads];
    for (int i = 0; i < threads; ++i)
        ios[i] = new BoolIO<NetIO>(new NetIO(party == ALICE ? nullptr : "127.0.0.1", port + i), party == ALICE);

    // test protocols (parity, threshold_and_sum) here (do not nest setup_zk_bool() calls)
    hello_world_zk(ios, party); 



    

    // test subroutines in here:
    setup_zk_bool<BoolIO<NetIO>>(ios, threads, party);

    Float a(1, ALICE);
    Float b(2, ALICE);
    Float x(5, ALICE);
    Float y(2, ALICE);
    cout << "dist(): " << dist(a,b,x,y).reveal<double>() << endl;


    vector<Integer> xs;
    xs.push_back(Integer(32, 2, ALICE));
    xs.push_back(Integer(32, 4, ALICE));
    xs.push_back(Integer(32, -2, ALICE));
    xs.push_back(Integer(32, 16, ALICE));
    xs.push_back(Integer(32, 8, ALICE));

    Integer s = example_vec_sum(xs);
    cout << "sum of xs: " << s.reveal<int>() << endl;

    bool cheat = finalize_zk_bool<BoolIO<NetIO>>();
    if (cheat)error("cheat!\n");
    
    for (int i = 0; i < threads; ++i) {
        delete ios[i]->io;
        delete ios[i];
    }
    return 0;
}
