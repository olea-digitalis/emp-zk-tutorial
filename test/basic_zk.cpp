#include <emp-zk/emp-zk.h>
#include <emp-tool/emp-tool.h>
#include <iostream>

using namespace emp;
using namespace std;

int port, party;
const int threads = 1;


void test_circuit_zk(BoolIO<NetIO> *ios[threads], int party) {
    setup_zk_bool<BoolIO<NetIO>>(ios, threads, party);
    Bit a(0, ALICE);
    Bit b(1, PUBLIC);
    
    cout << "reveal operator -- a: " << a.reveal<bool>() << "   b: " << b.reveal<bool>() << endl;
    cout << "AND operator -- a & b: " << (a & b).reveal() << endl;
    cout << "XOR operator -- a ^ b: " << (a ^ b).reveal() << endl;
    cout << "OR operator -- a | b: " << (a | b).reveal() << endl;
    cout << "NOT operator -- !a: " << (!a).reveal() << "    !b: " << (!b).reveal() << endl;

    bool cheat = finalize_zk_bool<BoolIO<NetIO>>();
    if (cheat)error("cheat!\n");
}

/*
void test_random_challenge(BoolIO<NetIO> *ios[threads], int party) {
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
*/



int main(int argc, char **argv) {
    parse_party_and_port(argv, &party, &port);
    BoolIO<NetIO> *ios[threads];
    for (int i = 0; i < threads; ++i)
        ios[i] = new BoolIO<NetIO>(new NetIO(party == ALICE ? nullptr : "127.0.0.1", port + i), party == ALICE);
    test_circuit_zk(ios, party);

    for (int i = 0; i < threads; ++i) {
        delete ios[i]->io;
        delete ios[i];
    }
    return 0;
}