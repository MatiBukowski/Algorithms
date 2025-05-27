//
// Created by mateu on 14.01.2025.
//

#include "measurements.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "genetic_algorithm.h"
#include "load.h"


using namespace std;

void measure_ftv47() {
    pair<int**, int> data = load_data("ftv47");
    int **matrix = data.first;

    Genetic_algorithm *gen_alg1 = new Genetic_algorithm(matrix, 48, 0.8, 0.1, "SPC", "swap", 60, 1, "ftv47");
    for(int i=0; i<10; i++) {
        gen_alg1->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg1;

    Genetic_algorithm *gen_alg2 = new Genetic_algorithm(matrix, 48, 0.8, 0.1, "SPC", "swap", 60, 2, "ftv47");
    for(int i=0; i<10; i++) {
        gen_alg2->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg2;

    Genetic_algorithm *gen_alg3 = new Genetic_algorithm(matrix, 48, 0.8, 0.1, "SPC", "swap", 60, 3, "ftv47");
    for(int i=0; i<10; i++) {
        gen_alg2->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg3;
    // --------------------------------------
    Genetic_algorithm *gen_alg4 = new Genetic_algorithm(matrix, 48, 0.8, 0.1, "SPC", "insert", 60, 1, "ftv47");
    for(int i=0; i<10; i++) {
        gen_alg4->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg4;

    Genetic_algorithm *gen_alg5 = new Genetic_algorithm(matrix, 48, 0.8, 0.1, "SPC", "insert", 60, 2, "ftv47");
    for(int i=0; i<10; i++) {
        gen_alg5->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg5;

    Genetic_algorithm *gen_alg6 = new Genetic_algorithm(matrix, 48, 0.8, 0.1, "SPC", "insert", 60, 3, "ftv47");
    for(int i=0; i<10; i++) {
        gen_alg6->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg6;
    // --------------------------------------
    // Genetic_algorithm *gen_alg7 = new Genetic_algorithm(matrix, 48, 0.8, 0.1, "CC", "swap", 60, 1, "ftv47");
    // for(int i=0; i<10; i++) {
    //     gen_alg7->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg7;
    //
    // Genetic_algorithm *gen_alg8 = new Genetic_algorithm(matrix, 48, 0.8, 0.1, "CC", "swap", 60, 2, "ftv47");
    // for(int i=0; i<10; i++) {
    //     gen_alg8->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg8;
    //
    // Genetic_algorithm *gen_alg9 = new Genetic_algorithm(matrix, 48, 0.8, 0.1, "CC", "swap", 60, 3, "ftv47");
    // for(int i=0; i<10; i++) {
    //     gen_alg9->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg9;
    // // --------------------------------------
    // Genetic_algorithm *gen_alg10 = new Genetic_algorithm(matrix, 48, 0.8, 0.1, "CC", "insert", 60, 1, "ftv47");
    // for(int i=0; i<10; i++) {
    //     gen_alg10->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg10;
    //
    // Genetic_algorithm *gen_alg11 = new Genetic_algorithm(matrix, 48, 0.8, 0.1, "CC", "insert", 60, 2, "ftv47");
    // for(int i=0; i<10; i++) {
    //     gen_alg11->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg11;
    //
    // Genetic_algorithm *gen_alg12 = new Genetic_algorithm(matrix, 48, 0.8, 0.1, "CC", "insert", 60, 3, "ftv47");
    // for(int i=0; i<10; i++) {
    //     gen_alg12->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg12;
}

void measure_ftv170() {
    pair<int**, int> data = load_data("ftv170");
     int** matrix = data.first;

    Genetic_algorithm *gen_alg1 = new Genetic_algorithm(matrix, 171, 0.8, 0.1, "SPC", "swap", 120, 1, "ftv170");
    for(int i=0; i<10; i++) {
        gen_alg1->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg1;

    Genetic_algorithm *gen_alg2 = new Genetic_algorithm(matrix, 171, 0.8, 0.1, "SPC", "swap", 120, 2, "ftv170");
    for(int i=0; i<10; i++) {
        gen_alg2->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg2;

    Genetic_algorithm *gen_alg3 = new Genetic_algorithm(matrix, 171, 0.8, 0.1, "SPC", "swap", 120, 3, "ftv170");
    for(int i=0; i<10; i++) {
        gen_alg2->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg3;
    // --------------------------------------
    Genetic_algorithm *gen_alg4 = new Genetic_algorithm(matrix, 171, 0.8, 0.1, "SPC", "insert", 120, 1, "ftv170");
    for(int i=0; i<10; i++) {
        gen_alg4->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg4;

    Genetic_algorithm *gen_alg5 = new Genetic_algorithm(matrix, 171, 0.8, 0.1, "SPC", "insert", 120, 2, "ftv170");
    for(int i=0; i<10; i++) {
        gen_alg5->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg5;

    Genetic_algorithm *gen_alg6 = new Genetic_algorithm(matrix, 171, 0.8, 0.1, "SPC", "insert", 120, 3, "ftv170");
    for(int i=0; i<10; i++) {
        gen_alg6->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg6;
    // --------------------------------------
    // Genetic_algorithm *gen_alg7 = new Genetic_algorithm(matrix, 171, 0.8, 0.1, "CC", "swap", 120, 1, "ftv170");
    // for(int i=0; i<10; i++) {
    //     gen_alg7->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg7;
    //
    // Genetic_algorithm *gen_alg8 = new Genetic_algorithm(matrix, 171, 0.8, 0.1, "CC", "swap", 120, 2, "ftv170");
    // for(int i=0; i<10; i++) {
    //     gen_alg8->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg8;
    //
    // Genetic_algorithm *gen_alg9 = new Genetic_algorithm(matrix, 171, 0.8, 0.1, "CC", "swap", 120, 3, "ftv170");
    // for(int i=0; i<10; i++) {
    //     gen_alg9->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg9;
    // // --------------------------------------
    // Genetic_algorithm *gen_alg10 = new Genetic_algorithm(matrix, 171, 0.8, 0.1, "CC", "insert", 120, 1, "ftv170");
    // for(int i=0; i<10; i++) {
    //     gen_alg10->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg10;
    //
    // Genetic_algorithm *gen_alg11 = new Genetic_algorithm(matrix, 171, 0.8, 0.1, "CC", "insert", 120, 2, "ftv170");
    // for(int i=0; i<10; i++) {
    //     gen_alg11->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg11;
    //
    // Genetic_algorithm *gen_alg12 = new Genetic_algorithm(matrix, 171, 0.8, 0.1, "CC", "insert", 120, 3, "ftv170");
    // for(int i=0; i<10; i++) {
    //     gen_alg12->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg12;
}

void measure_rbg403() {
    pair<int**, int> data = load_data("rbg403");
    int **matrix = data.first;

    Genetic_algorithm *gen_alg1 = new Genetic_algorithm(matrix, 403, 0.8, 0.1, "SPC", "swap", 200, 1, "rbg403");
    for(int i=0; i<10; i++) {
        gen_alg1->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg1;

    Genetic_algorithm *gen_alg2 = new Genetic_algorithm(matrix, 403, 0.8, 0.1, "SPC", "swap", 200, 2, "rbg403");
    for(int i=0; i<10; i++) {
        gen_alg2->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg2;

    Genetic_algorithm *gen_alg3 = new Genetic_algorithm(matrix, 403, 0.8, 0.1, "SPC", "swap", 200, 3, "rbg403");
    for(int i=0; i<10; i++) {
        gen_alg3->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg3;
    // --------------------------------------
    Genetic_algorithm *gen_alg4 = new Genetic_algorithm(matrix, 403, 0.8, 0.1, "SPC", "insert", 200, 1, "rbg403");
    for(int i=0; i<10; i++) {
        gen_alg4->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg4;

    Genetic_algorithm *gen_alg5 = new Genetic_algorithm(matrix, 403, 0.8, 0.1, "SPC", "insert", 200, 2, "rbg403");
    for(int i=0; i<10; i++) {
        gen_alg5->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg5;

    Genetic_algorithm *gen_alg6 = new Genetic_algorithm(matrix, 403, 0.8, 0.1, "SPC", "insert", 200, 3, "rbg403");
    for(int i=0; i<10; i++) {
        gen_alg6->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg6;
    // --------------------------------------
//     Genetic_algorithm *gen_alg7 = new Genetic_algorithm(matrix, 403, 0.8, 0.1, "CC", "swap", 200, 1, "rbg403");
//     for(int i=0; i<10; i++) {
//         gen_alg7->geneticAlgorithm();
//         this_thread::sleep_for(std::chrono::milliseconds(100));
//     }
//     delete gen_alg7;
//
//     Genetic_algorithm *gen_alg8 = new Genetic_algorithm(matrix, 403, 0.8, 0.1, "CC", "swap", 200, 2, "rbg403");
//     for(int i=0; i<10; i++) {
//         gen_alg8->geneticAlgorithm();
//         this_thread::sleep_for(std::chrono::milliseconds(100));
//     }
//     delete gen_alg8;
//
//     Genetic_algorithm *gen_alg9 = new Genetic_algorithm(matrix, 403, 0.8, 0.1, "CC", "swap", 200, 3, "rbg403");
//     for(int i=0; i<10; i++) {
//         gen_alg9->geneticAlgorithm();
//         this_thread::sleep_for(std::chrono::milliseconds(100));
//     }
//     delete gen_alg9;
//     // --------------------------------------
//     Genetic_algorithm *gen_alg10 = new Genetic_algorithm(matrix, 403, 0.8, 0.1, "CC", "insert", 200, 1, "rbg403");
//     for(int i=0; i<10; i++) {
//         gen_alg10->geneticAlgorithm();
//         this_thread::sleep_for(std::chrono::milliseconds(100));
//     }
//     delete gen_alg10;
//
//     Genetic_algorithm *gen_alg11 = new Genetic_algorithm(matrix, 403, 0.8, 0.1, "CC", "insert", 200, 2, "rbg403");
//     for(int i=0; i<10; i++) {
//         gen_alg11->geneticAlgorithm();
//         this_thread::sleep_for(std::chrono::milliseconds(100));
//     }
//     delete gen_alg11;
//
//     Genetic_algorithm *gen_alg12 = new Genetic_algorithm(matrix, 403, 0.8, 0.1, "CC", "insert", 200, 3, "rbg403");
//     for(int i=0; i<10; i++) {
//         gen_alg12->geneticAlgorithm();
//         this_thread::sleep_for(std::chrono::milliseconds(100));
//     }
//     delete gen_alg12;
}


// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void measure_ftv47_for_best_population_size() {
    pair<int**, int> data = load_data("ftv47");
    int **matrix = data.first;

    Genetic_algorithm *gen_alg1 = new Genetic_algorithm(matrix, 48, 0.55, 0.1, "CC", "insert", 60, 3, "ftv47");
    for(int i=0; i<10; i++) {
        gen_alg1->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg1;

    Genetic_algorithm *gen_alg2 = new Genetic_algorithm(matrix, 48, 0.75, 0.1, "CC", "insert", 60, 3, "ftv47");
    for(int i=0; i<10; i++) {
        gen_alg2->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg2;

    Genetic_algorithm *gen_alg3 = new Genetic_algorithm(matrix, 48, 0.9, 0.1, "CC", "insert", 60, 3, "ftv47");
    for(int i=0; i<10; i++) {
        gen_alg2->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg3;
    // --------------------------------------
    Genetic_algorithm *gen_alg4 = new Genetic_algorithm(matrix, 48, 0.55, 0.1, "SPC", "insert", 60, 3, "ftv47");
    for(int i=0; i<10; i++) {
        gen_alg4->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg4;

    Genetic_algorithm *gen_alg5 = new Genetic_algorithm(matrix, 48, 0.75, 0.1, "SPC", "insert", 60, 3, "ftv47");
    for(int i=0; i<10; i++) {
        gen_alg5->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg5;

    Genetic_algorithm *gen_alg6 = new Genetic_algorithm(matrix, 48, 0.9, 0.1, "SPC", "insert", 60, 3, "ftv47");
    for(int i=0; i<10; i++) {
        gen_alg6->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg6;
    // --------------------------------------
    // Genetic_algorithm *gen_alg7 = new Genetic_algorithm(matrix, 48, 0.8, 0.25, "CC", "swap", 60, 3, "ftv47");
    // for(int i=0; i<10; i++) {
    //     gen_alg7->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg7;
    //
    // Genetic_algorithm *gen_alg8 = new Genetic_algorithm(matrix, 48, 0.8, 0.35, "CC", "swap", 60, 3, "ftv47");
    // for(int i=0; i<10; i++) {
    //     gen_alg8->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg8;
    //
    // Genetic_algorithm *gen_alg9 = new Genetic_algorithm(matrix, 48, 0.8, 0.5, "CC", "swap", 60, 3, "ftv47");
    // for(int i=0; i<10; i++) {
    //     gen_alg9->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg9;
    // // --------------------------------------
    // Genetic_algorithm *gen_alg10 = new Genetic_algorithm(matrix, 48, 0.8, 0.25, "CC", "insert", 60, 3, "ftv47");
    // for(int i=0; i<10; i++) {
    //     gen_alg10->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg10;
    //
    // Genetic_algorithm *gen_alg11 = new Genetic_algorithm(matrix, 48, 0.8, 0.35, "CC", "insert", 60, 3, "ftv47");
    // for(int i=0; i<10; i++) {
    //     gen_alg11->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg11;
    //
    // Genetic_algorithm *gen_alg12 = new Genetic_algorithm(matrix, 48, 0.8, 0.5, "CC", "insert", 60, 3, "ftv47");
    // for(int i=0; i<10; i++) {
    //     gen_alg12->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg12;
}

void measure_ftv170_for_best_population_size() {
    pair<int**, int> data = load_data("ftv170");
     int** matrix = data.first;

    Genetic_algorithm *gen_alg1 = new Genetic_algorithm(matrix, 171, 0.55, 0.1, "CC", "insert", 120, 3, "ftv170");
    for(int i=0; i<10; i++) {
        gen_alg1->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg1;

    Genetic_algorithm *gen_alg2 = new Genetic_algorithm(matrix, 171, 0.75, 0.1, "CC", "insert", 120, 3, "ftv170");
    for(int i=0; i<10; i++) {
        gen_alg2->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg2;

    Genetic_algorithm *gen_alg3 = new Genetic_algorithm(matrix, 171, 0.9, 0.1, "CC", "insert", 120, 3, "ftv170");
    for(int i=0; i<10; i++) {
        gen_alg2->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg3;
    // --------------------------------------
    Genetic_algorithm *gen_alg4 = new Genetic_algorithm(matrix, 171, 0.55, 0.1, "SPC", "insert", 120, 3, "ftv170");
    for(int i=0; i<10; i++) {
        gen_alg4->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg4;

    Genetic_algorithm *gen_alg5 = new Genetic_algorithm(matrix, 171, 0.75, 0.1, "SPC", "insert", 120, 3, "ftv170");
    for(int i=0; i<10; i++) {
        gen_alg5->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg5;

    Genetic_algorithm *gen_alg6 = new Genetic_algorithm(matrix, 171, 0.9, 0.1, "SPC", "insert", 120, 3, "ftv170");
    for(int i=0; i<10; i++) {
        gen_alg6->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg6;
    // --------------------------------------
    // Genetic_algorithm *gen_alg7 = new Genetic_algorithm(matrix, 171, 0.8, 0.25, "CC", "swap", 120, 3, "ftv170");
    // for(int i=0; i<10; i++) {
    //     gen_alg7->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg7;
    //
    // Genetic_algorithm *gen_alg8 = new Genetic_algorithm(matrix, 171, 0.8, 0.35, "CC", "swap", 120, 3, "ftv170");
    // for(int i=0; i<10; i++) {
    //     gen_alg8->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg8;
    //
    // Genetic_algorithm *gen_alg9 = new Genetic_algorithm(matrix, 171, 0.8, 0.5, "CC", "swap", 120, 3, "ftv170");
    // for(int i=0; i<10; i++) {
    //     gen_alg9->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg9;
    // // --------------------------------------
    // Genetic_algorithm *gen_alg10 = new Genetic_algorithm(matrix, 171, 0.8, 0.25, "CC", "insert", 120, 3, "ftv170");
    // for(int i=0; i<10; i++) {
    //     gen_alg10->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg10;
    //
    // Genetic_algorithm *gen_alg11 = new Genetic_algorithm(matrix, 171, 0.8, 0.35, "CC", "insert", 120, 3, "ftv170");
    // for(int i=0; i<10; i++) {
    //     gen_alg11->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg11;
    //
    // Genetic_algorithm *gen_alg12 = new Genetic_algorithm(matrix, 171, 0.8, 0.5, "CC", "insert", 120, 3, "ftv170");
    // for(int i=0; i<10; i++) {
    //     gen_alg12->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg12;
}

void measure_rbg403_for_best_population_size() {
    pair<int**, int> data = load_data("rbg403");
    int **matrix = data.first;

    Genetic_algorithm *gen_alg1 = new Genetic_algorithm(matrix, 403, 0.55, 0.1, "CC", "insert", 200, 3, "rbg403");
    for(int i=0; i<10; i++) {
        gen_alg1->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg1;

    Genetic_algorithm *gen_alg2 = new Genetic_algorithm(matrix, 403, 0.75, 0.1, "CC", "insert", 200, 3, "rbg403");
    for(int i=0; i<10; i++) {
        gen_alg2->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg2;

    Genetic_algorithm *gen_alg3 = new Genetic_algorithm(matrix, 403, 0.9, 0.1, "CC", "insert", 200, 3, "rbg403");
    for(int i=0; i<10; i++) {
        gen_alg2->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg3;
    // --------------------------------------
    Genetic_algorithm *gen_alg4 = new Genetic_algorithm(matrix, 403, 0.55, 0.1, "SPC", "insert", 200, 3, "rbg403");
    for(int i=0; i<10; i++) {
        gen_alg4->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg4;

    Genetic_algorithm *gen_alg5 = new Genetic_algorithm(matrix, 403, 0.75, 0.1, "SPC", "insert", 200, 3, "rbg403");
    for(int i=0; i<10; i++) {
        gen_alg5->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg5;

    Genetic_algorithm *gen_alg6 = new Genetic_algorithm(matrix, 403, 0.9, 0.1, "SPC", "insert", 200, 3, "rbg403");
    for(int i=0; i<10; i++) {
        gen_alg6->geneticAlgorithm();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete gen_alg6;
    // --------------------------------------
    // Genetic_algorithm *gen_alg7 = new Genetic_algorithm(matrix, 403, 0.8, 0.25, "CC", "swap", 200, 3, "rbg403");
    // for(int i=0; i<10; i++) {
    //     gen_alg7->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg7;
    //
    // Genetic_algorithm *gen_alg8 = new Genetic_algorithm(matrix, 403, 0.8, 0.35, "CC", "swap", 200, 3, "rbg403");
    // for(int i=0; i<10; i++) {
    //     gen_alg8->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg8;
    //
    // Genetic_algorithm *gen_alg9 = new Genetic_algorithm(matrix, 403, 0.8, 0.5, "CC", "swap", 200, 3, "rbg403");
    // for(int i=0; i<10; i++) {
    //     gen_alg9->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg9;
    // // --------------------------------------
    // Genetic_algorithm *gen_alg10 = new Genetic_algorithm(matrix, 403, 0.8, 0.25, "CC", "insert", 200, 3, "rbg403");
    // for(int i=0; i<10; i++) {
    //     gen_alg10->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg10;
    //
    // Genetic_algorithm *gen_alg11 = new Genetic_algorithm(matrix, 403, 0.8, 0.35, "CC", "insert", 200, 3, "rbg403");
    // for(int i=0; i<10; i++) {
    //     gen_alg11->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg11;
    //
    // Genetic_algorithm *gen_alg12 = new Genetic_algorithm(matrix, 403, 0.8, 0.5, "CC", "insert", 200, 3, "rbg403");
    // for(int i=0; i<10; i++) {
    //     gen_alg12->geneticAlgorithm();
    //     this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    // delete gen_alg12;
}