//
// Created by david on 27.03.2022.
//

#ifndef LAB6_7_TESTS_H
#define LAB6_7_TESTS_H


class Tests {
public:
    static void runAll();
private:
    static void createDestroyTest();
    /*
     * repo tests:
     */
    static void addRepoTest();
    static void delRepoTest();
    static void modRepoTest();

    /*
     *srv tests:
     */
    static void addSrvTest();
    static void delSrvTest();
    static void modSrvTest();
};


#endif //LAB6_7_TESTS_H
