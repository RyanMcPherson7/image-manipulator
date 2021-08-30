#include "Functionality.h"

int main() {

    vector<Image> input;        //these vectors are organized in the same way
    vector<Image> examples;     //as the given files
    vector<Image> output;
    vector<Image> temp;         //stores temp images for tests

    //read the input files
    //done this way to avoid
    //reading the same file twice
    ReadTGA(input, "input/car.tga");            // index 0
    ReadTGA(input, "input/circles.tga");        // index 1
    ReadTGA(input, "input/layer1.tga");         // index 2
    ReadTGA(input, "input/layer2.tga");         // index 3
    ReadTGA(input, "input/layer_blue.tga");     // index 4
    ReadTGA(input, "input/layer_green.tga");    // index 5
    ReadTGA(input, "input/layer_red.tga");      // index 6
    ReadTGA(input, "input/pattern1.tga");       // index 7
    ReadTGA(input, "input/pattern2.tga");       // index 8
    ReadTGA(input, "input/text.tga");           // index 9
    ReadTGA(input, "input/text2.tga");          // index 10

    //read the example files to compare to output
    ReadTGA(examples, "examples/EXAMPLE_part1.tga");        // index 0
    ReadTGA(examples, "examples/EXAMPLE_part2.tga");        // index 1
    ReadTGA(examples, "examples/EXAMPLE_part3.tga");        // index 2
    ReadTGA(examples, "examples/EXAMPLE_part4.tga");        // index 3
    ReadTGA(examples, "examples/EXAMPLE_part5.tga");        // index 4
    ReadTGA(examples, "examples/EXAMPLE_part6.tga");        // index 5
    ReadTGA(examples, "examples/EXAMPLE_part7.tga");        // index 6
    ReadTGA(examples, "examples/EXAMPLE_part8_b.tga");      // index 7
    ReadTGA(examples, "examples/EXAMPLE_part8_g.tga");      // index 8
    ReadTGA(examples, "examples/EXAMPLE_part8_r.tga");      // index 9
    ReadTGA(examples, "examples/EXAMPLE_part9.tga");        // index 10
    ReadTGA(examples, "examples/EXAMPLE_part10.tga");       // index 11
    ReadTGA(examples, "examples/EXAMPLE_extracredit.tga");  // index 12

    //running tests

    //TEST 1
    Multiply(output, input.at(2), input.at(7), "output/part1.tga");

    //TEST 2
    Subtract(output, input.at(3), input.at(0), "output/part2.tga");

    //TEST 3
    Multiply(temp, input.at(2), input.at(8), "output/part3.tga");
    Screen(output, input.at(9), temp.at(0), "output/part3.tga");

    //TEST 4
    Multiply(temp, input.at(3), input.at(1), "output/part4.tga");
    Subtract(output, input.at(8), temp.at(1), "output/part4.tga");

    //TEST 5
    Overlay(output, input.at(2), input.at(7), "output/part5.tga");

    //TEST 6
    AddGreen(output, input.at(0), 200, "output/part6.tga");

    //TEST 7
    ScaleRedAndBlue(output, input.at(0), 4, 0, "output/part7.tga");

    //TEST 8
    Separate(output, input.at(0), "blue", "output/part8_b.tga");
    Separate(output, input.at(0), "green", "output/part8_g.tga");
    Separate(output, input.at(0), "red", "output/part8_r.tga");

    //TEST 9
    Combine(output, input.at(6), input.at(5), input.at(4), "output/part9.tga");

    //TEST 10
    Flip180(output, input.at(10), "output/part10.tga");

    //EXTRA CREDIT
    Quad(output, input.at(0), input.at(1), input.at(9), input.at(7), "output/extracredit.tga");


    //checking for correct output
    unsigned int count = 0;

    for (unsigned int i = 0; i < output.size(); i++) {

        //comparing example to output
        if (output.at(i) == examples.at(i)) {
            cout << "Test #" << i + 1 << "......Passed!" << endl;
            count++;
        }
        else
            cout << "Test #" << i + 1 << "......Failed!" << endl;
    }

    //print final results
    cout << "Test Results: " << count << " / 13";

    return 0;
}