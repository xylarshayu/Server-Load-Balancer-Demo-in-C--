#include "request.cpp"
#include "webserver.cpp"
#include "loadbalancer.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream> /* Easy way to create strings without concatenation */

using namespace std;

const int NUMWEBSERVERS = 5;

// Request creation
request createRandomRequest()
{
    stringstream ips, ipd;
    request r;

    /*Random IP addresses for demo sake */
    ips << (rand() % 255) << "." << (rand() % 255) << "." << (rand() % 255) << "." << (rand() % 255); /* Source IP */
    ipd << (rand() % 255) << "." << (rand() % 255) << "." << (rand() % 255) << "." << (rand() % 255); /* Destination IP */

    r.source = ips.str();
    r.destination = ipd.str();
    r.processTime = rand() % 500;
    return r;
}

int main()
{
    // RNG so there's a new request at every random amount of time
    srand(time(0));
    // Create load balancer
    loadbalancer lb;
    // start off with a populated queue
    for (int i = 0; i < 10; i++) {
        request r = (createRandomRequest());
        lb.addRequest(r);
    }
    // Array of webservers
    webserver webarray[NUMWEBSERVERS];
    for (int i = 0; i < NUMWEBSERVERS; i++) {
        webserver w((char)(i + 65));
        webarray[i] = w;
        webarray[i].addRequest(lb.getRequest(), lb.getTime());
    }

    // loop
    while (lb.getTime() < 10000) {
        int currTime = lb.getTime();
        // check each webserver for if it's done
        if (webarray[currTime % NUMWEBSERVERS].isRequestDone(currTime)) { /* At a time a single webserver is asked if they're done, starting with box 0++*/
            request r = webarray[currTime %  NUMWEBSERVERS].getRequest();
            cout << "At " << currTime << " " << webarray[currTime %  NUMWEBSERVERS].getName() << " processed request from " << r.source << " to " << r.destination << endl;
            // then assign new req
            webarray[currTime % NUMWEBSERVERS].addRequest(lb.getRequest(), currTime);
        }
        /* To access the actual web array being dealt with rather than just a copy of it, it's referred to in full every time */

        if (rand() % 10 == 0) {
            request r = (createRandomRequest());
            lb.addRequest(r);
        }
        lb.incTime();
    }
    int press;
    press = getchar();
}
