#include <iostream>
#include <fstream>
#include "SerialPort.h"

using namespace std;

int main() {
    SerialPort serialPort("COM3", 9600); 
    if (serialPort.isConnected()) {
        ofstream myfile; // create a text document object
        myfile.open("data.txt"); // open the text document
        while (true) {
            string data = serialPort.readSerialPort();
            if (!data.empty()) {
                myfile << data << endl; // write the data to the text document
            }
        }
        myfile.close(); // close the text document
    } else {
        cout << "Serial port connection failed!" << endl;
    }
    return 0;
}
