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


void test_bit_operations_zk(BoolIO<NetIO> *ios[threads], int party) {
    setup_zk_bool<BoolIO<NetIO>>(ios, threads, party);
    Bit a(0, ALICE); // commits to a private bit a=0
    Bit b(1, PUBLIC); // commits to a public bit b=1
    
    cout << "Reveal -----------------------------------------------" << endl;
    cout << "reveal operator -- a: " << a.reveal<bool>() << "   b: " << b.reveal<bool>() << endl;
    cout << endl;
    cout << "Logical Operators ------------------------------------" << endl;
    cout << "AND operator -- a & b: " << (a & b).reveal() << endl;
    cout << "XOR operator -- a ^ b: " << (a ^ b).reveal() << endl;
    cout << "OR operator -- a | b: " << (a | b).reveal() << endl;
    cout << "NOT operator -- !a: " << (!a).reveal() << "    !b: " << (!b).reveal() << endl;
    cout << endl;
    cout << "Comparison Operators -----------------------------------" << endl;
    cout << "a==b: " << (a == b).reveal() << endl;
    cout << "a!=b: " << (a != b).reveal() << endl;
    cout << "--------------------------------------------------------" << endl;


    bool cheat = finalize_zk_bool<BoolIO<NetIO>>();
    if (cheat)error("cheat!\n");
}

// Integers are collections of Bits
// operations on integers are compiled into collections of ZK bitwise operations
void test_int_operations_zk(BoolIO<NetIO> *ios[threads], int party) {
    setup_zk_bool<BoolIO<NetIO>>(ios, threads, party);

    Integer a(32, 5, ALICE); // size in bits, value, party
    Integer b(32, 2, ALICE);
    Integer c(32, -3, ALICE);

    cout << "Reveal -----------------------------------------------" << endl;
    cout << "reveal operator -- a: " << a.reveal<int>() << "   b: " << b.reveal<int>() << "   c: " << c.reveal<int>() << endl;
    cout << endl;

    cout << "Arithmetic Operators ------------------------------------" << endl;
    cout << "Addition -- a+b: " << (a+b).reveal<int>() << endl;
    cout << "Subtraction -- a-b: " << (a-b).reveal<int>() << endl;
    cout << "Multiplication -- a*b: " << (a*b).reveal<int>() << endl;
    cout << "Division -- a/b: " << (a/b).reveal<int>() << endl;
    cout << "Modulus -- a%b: " << (a%b).reveal<int>() << endl;
    cout << endl;

    cout << "Comparison Operators -----------------------------------" << endl;
    cout << "a==b: " << (a==b).reveal() << endl;
    cout << "a!=b: " << (a!=b).reveal() << endl;
    cout << "a>b: " << (a>b).reveal() << endl;
    cout << "a>=b: " << (a>=b).reveal() << endl;
    cout << "a<b: " << (a<b).reveal() << endl;
    cout << "a<=b: " << (a<=b).reveal() << endl;
    cout << endl;

    cout << "(Integer) Bitwise Operators ------------------------------------" << endl;
    cout << "AND operator -- a & b: " << (a & b).reveal<int>() << endl;
    cout << "XOR operator -- a ^ b: " << (a ^ b).reveal<int>() << endl;
    cout << "OR operator -- a | b: " << (a | b).reveal<int>() << endl;
    cout << "(Left/Right) Shift by public value -- a << 2: " << (a<<2).reveal<int>() << endl;
    cout << "(Left/Right) Shift by private value -- a >> b: " << (a>>b).reveal<int>() << endl;
    cout << endl;

    bool cheat = finalize_zk_bool<BoolIO<NetIO>>();
    if (cheat)error("cheat!\n");
}


void test_control_flow_zk(BoolIO<NetIO> *ios[threads], int party) {
    setup_zk_bool<BoolIO<NetIO>>(ios, threads, party);

    Integer a(32, 5, ALICE); // size in bits, value, party
    Integer b(32, 2, ALICE);


    // if statements?
    /*
    // compiler error (why?)
    if (a>b) {
        cout << "program branch 1" << endl;
    } else {
        cout << "program branch 2" << endl;
    }
    
    // Bob can observe the behavior of the program to get information about the hidden values
    */

    // this won't throw an error, but it leaks information explicitly
    // only want to do this if we *intend* to output info about the comparison between a & b
    Bit comp = a>b;
    if (comp.reveal()) {
        cout << "program branch 1" << endl;
    } else {
        cout << "program branch 2" << endl;
    }

    // we can replace if statements

    // the select operator allows us to propagate the result of a comparison
    // to other values in the program *without* leaking information
    Integer x(32, 5, PUBLIC);
    Integer y(32, -5, PUBLIC);
    comp = a<b;

    Integer result = x.select(comp, y);
    // result = x if comp = 0,   y if comp = 1   (1 'performs' the select, 0 does not)

    // and now the value result may be used downstream
    // in this instance, we will reveal it just to show you the result.

    cout << "result: " << result.reveal<int>() << endl;

    bool cheat = finalize_zk_bool<BoolIO<NetIO>>();
    if (cheat)error("cheat!\n");
}

// emp implements IEEE single precision floating point numbers, built from collections of Bits
// as with Integers, Float operations are compiled into collections of ZK bitwise operations
void test_float_operations_zk(BoolIO<NetIO> *ios[threads], int party) {
    Float a(2.5, ALICE);
    Float b(1.5, ALICE);

    cout << "Arithmetic Operators ------------------------------------" << endl;
    cout << "Addition -- a+b: " << (a+b).reveal<double>() << endl;
    cout << "Subtraction -- a-b: " << (a-b).reveal<double>() << endl;
    cout << "Multiplication -- a*b: " << (a*b).reveal<double>() << endl;
    cout << "Division -- a/b: " << (a/b).reveal<double>() << endl;
    cout << "Exponentiation e^a -- a.exp(): " << (a.exp()).reveal<double>() << endl;
    cout << "Exponentiation 2^a -- a.exp2()" << (a.exp2()).reveal<double>() << endl;
    cout << endl;

}


void test_coin_flip(BoolIO<NetIO> *ios[threads], int party) {
    setup_zk_bool<BoolIO<NetIO>>(ios, threads, party);
    BoolIO<NetIO> *io = ios[0];

    PRG prg;
    block r;
    prg.random_block(&r, 1);
    bool r_in_bits[128];
    block_to_bool(r_in_bits, r);
    Bit a(r_in_bits[0], ALICE);
    bool s_in_bits[128];
    
    if (party == ALICE) {
        block s;
        io->recv_block(&s, 1);
        block_to_bool(s_in_bits, s);
    } else {
        block s;
        PRG prg;
        prg.random_block(&s, 1);
        io->send_block(&s, 1);
        io->flush();
        block_to_bool(s_in_bits, s);
    }
    
    Bit b(s_in_bits[0], PUBLIC);
    Bit c = a ^ b;
    cout << "random coin: " << c.reveal() << endl;

    bool cheat = finalize_zk_bool<BoolIO<NetIO>>();
    if (cheat)error("cheat!\n");
}


int main(int argc, char **argv) {
    parse_party_and_port(argv, &party, &port);
    BoolIO<NetIO> *ios[threads];
    for (int i = 0; i < threads; ++i)
        ios[i] = new BoolIO<NetIO>(new NetIO(party == ALICE ? nullptr : "127.0.0.1", port + i), party == ALICE);
    hello_world_zk(ios,party);

    cout << "\n\n";

    test_bit_operations_zk(ios, party);

    cout << "\n\n";

    test_int_operations_zk(ios, party);

    cout << "\n\n";
    
    test_control_flow_zk(ios, party);
    for (int i = 0; i < threads; ++i) {
        delete ios[i]->io;
        delete ios[i];
    }
    return 0;
}