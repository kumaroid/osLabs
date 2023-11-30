#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <memory>
#include <stdlib.h>

#include "parent.hpp"

namespace fs = std::filesystem;

std::string inputFile = "input.txt";
std::string output1File = "output1.txt";
std::string output2File = "output2.txt";

void RemoveIfExists(const std::string& name) {
    if (fs::exists(name)) {
        fs::remove(name);
    }
}

void Check(const std::vector<std::string> &input,
           const std::vector<std::string> &expOutput1,
           const std::vector<std::string> &expOutput2) {
    {
        auto inFile = std::ofstream(inputFile);

        inFile << output1File << '\n';
        inFile << output2File << '\n';

        for(const auto& line : input) {
            inFile << line << '\n';
        }
    }

    std::ifstream inFile(inputFile);

    ASSERT_NE(getenv("PATH_TO_CHILD"), nullptr);

    ParentRoutine(getenv("PATH_TO_CHILD"), inFile);

    auto outFile1 = std::ifstream(output1File);
    auto outFile2 = std::ifstream(output2File);

    ASSERT_TRUE(outFile1.good());
    ASSERT_TRUE(outFile2.good());

    std::vector<std::string> output1;
    std::vector<std::string> output2;
    for (std::string line; std::getline(outFile1, line); ) {
        output1.push_back(line);
    }
    for (std::string line; std::getline(outFile2, line); ) {
        output2.push_back(line);
    }

    ASSERT_TRUE(output1.size() == expOutput1.size());
    for (size_t i = 0; i < output1.size(); i++) {
        EXPECT_EQ(output1[i], expOutput1[i]);
    }

    ASSERT_TRUE(output2.size() == expOutput2.size());
    for (size_t i = 0; i < output2.size(); i++) {
        EXPECT_EQ(output2[i], expOutput2[i]);
    }

    inFile.close();
    outFile1.close();
    outFile2.close();
}

TEST(Lab1, Test1) {
    std::vector<std::string> input = {
        "bebra",
        "kumar",
        "meow"
    };

    std::vector<std::string> out1 = {
        "arbeb",
        "ramuk"
    };

    std::vector<std::string> out2 = {
        "woem"
    };

    Check(input, out1, out2);
}

TEST(Lab1, Test2) {
       std::vector<std::string> input = {
        "arbeb",
        "ramuk",
        "woem"
    };

    std::vector<std::string> out1 = {
        "bebra",
        "kumar"
    };

    std::vector<std::string> out2 = {
        "meow"
    };

    Check(input, out1, out2);
   
}


TEST(Lab1, Test3) {
    std::vector<std::string> input = {  };

    std::vector<std::string> out1 = {  };

    std::vector<std::string> out2 = {  };
    Check(input, out1, out2);
}

TEST(Lab1, Test4) {
    std::vector<std::string> input = {
        "12345",
        "kumar",
        "1337"
    };

    std::vector<std::string> out1 = {
        "54321",
        "ramuk"
    };

    std::vector<std::string> out2 = {
        "7331"
    };

    Check(input, out1, out2);
}

int main(int argc, char ** argv) {
    testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    RemoveIfExists(inputFile);
    RemoveIfExists(output1File);
    RemoveIfExists(output2File);
    return result;
}
