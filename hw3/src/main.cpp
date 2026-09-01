#include <iostream>
#include <gtest/gtest.h>
#include "bst.h"

int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        BST::Node left;
        BST::Node right;
        std::cout<<left<<right;
        BST::Node root(3, &left, &right);
        std::cout<<root;

        std::cout<< (root<3) <<std::endl;
        std::cout<< (root>3) <<std::endl;
        std::cout<< (root>=3) <<std::endl;
        std::cout<< (root<=3) <<std::endl;
        std::cout<< (root==3) <<std::endl;
        
        std::cout<< (3<root) <<std::endl;
        std::cout<< (3<=root) <<std::endl;
        std::cout<< (3>root) <<std::endl;
        std::cout<< (3>=root) <<std::endl;
        std::cout<< (3==root) <<std::endl;
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;   
}