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

// write a protocol which proves which of two publicly known cluster centers a hidden point (x1,x2) is closer to
// the protocol will involve:
//     - a 2-dimensional cluster center a = (a1, a2)   (committed publicly)
//     - a 2-dimensional cluster center b = (b1, b2)   (committed publicly)
//     - a 2-dimensional point x=(x1, x2)              (known only to Alice)
// it should reveal a result Bit. Its value should be:
//     - 0 if x is closer to a
//     - 1 if x is closer to b
void which_cluster(BoolIO<NetIO> *ios[threads], int party) {
    setup_zk_bool<BoolIO<NetIO>>(ios, threads, party);

    Float a1(5.5, PUBLIC);
    Float a2(10.0, PUBLIC);
    Float b1(-1.2, PUBLIC);
    Float b2(2.1, PUBLIC);

    Float x1(12.0, ALICE);
    Float x2(11.5, ALICE);

    // YOUR CODE HERE

    Bit result(0, ALICE);
    cout << result.reveal() << endl;
    bool cheat = finalize_zk_bool<BoolIO<NetIO>>();
    if (cheat)error("cheat!\n");
}





// write a subroutine for a proof of logistic regression inference.
//     if you're not familiar with logistic regression, check out: https://datatab.net/tutorial/logistic-regression
//     (you dont need to read the Maximum Likelihood Method section, or anything below it)
// inputs: 
//     - a 3 dimensional set of weights w1, w2, w3  as Floats
//     - a 3 dimensional data point x1, x2, x3 as Floats
// output:
//     - f(x1,x2,x3), where f is the logistic function weighted by w1,w2,w3
Float logistic_regression_inference(Float w1, Float w2, Float w3, Float x1, Float x2, Float x3) {
    // YOUR CODE HERE
    Float result(-1, ALICE);
    return result;
}


// write a subroutine which proves that all (committed, hidden) points in a cluster are within distance d of a hidden cluster center
// inputs:
//     - a vector<Float> c, which represents a 2-dimensional cluster center.
//     - a Float d, which gives the maximum acceptable distance from the cluster center
//     - a vector< vector<Float> > xs, which represents 2-dimensional data points. The inner vectors should each have 2 entries.
// output:
//     - a Bit with value 1 if all the data points are at most d distance from c
//     - a Bit with value 0 otherwise

Bit threshold_cluster_distance(vector<Float> c, Float d, vector< vector<Float> > xs) {
    // YOUR CODE HERE
    Bit result(0, ALICE);
    return result;
}

// write a subroutine which trains a logistic regression model using gradient descent
//     - if you don't know what that means, research it online or get help from a colleague
// the subroutine should take in a vector<Float> ws, a vector< vector<Float> > xs, and a vector<Float> ys
// representing weights, data points, and true labels respectively.
// It should output a set of trained model weights.
vector<Float> logistic_regression_training() {
    // YOUR CODE HERE
    vector<Float> ret;
    return ret;
}




int main(int argc, char **argv) {
    parse_party_and_port(argv, &party, &port);
    BoolIO<NetIO> *ios[threads];
    for (int i = 0; i < threads; ++i)
        ios[i] = new BoolIO<NetIO>(new NetIO(party == ALICE ? nullptr : "127.0.0.1", port + i), party == ALICE);

    hello_world_zk(ios, party); 
    
    for (int i = 0; i < threads; ++i) {
        delete ios[i]->io;
        delete ios[i];
    }
    return 0;
}