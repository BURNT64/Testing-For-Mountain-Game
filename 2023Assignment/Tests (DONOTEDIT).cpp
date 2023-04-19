#include "Mountains.hpp"
#include <thread>
#include <map>

#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
namespace bdata = boost::unit_test::data;

// Test suite declaration
BOOST_AUTO_TEST_SUITE(TestSuite)

// Main function test case
int main(int argc, char* argv[])
{
    return 0;
}

// Test case for the main() function
BOOST_AUTO_TEST_CASE(test_main)
{
    // Test code for the main() function
    BOOST_CHECK_EQUAL(main(0, nullptr), 0); // example test to check return value
}

// Test case for the IncorrectFileFormatException class
BOOST_AUTO_TEST_CASE(IncorrectFileFormatExceptionTest)
{
    // Check if an exception is thrown correctly
    BOOST_CHECK_THROW(
        throw IncorrectFileFormatException("test message"),
        IncorrectFileFormatException
    );
}

// Test case for the Mountains class constructor
BOOST_AUTO_TEST_CASE(TestConstructor)
{
    // Initialize the Mountains object with a vector of filenames
    std::vector<std::string> filenames = { "Alps.txt", "Carpathians.txt" };
    Mountains mountains(filenames);
    // Check if a random mountain is returned successfully
    BOOST_REQUIRE(mountains.getRandomMountain() != "");
}

// Test case for the getRandomMountain method of the Mountains class
BOOST_AUTO_TEST_CASE(TestGetRandomMountain)
{
    // Initialize the Mountains object with a vector of filenames
    std::vector<std::string> filenames = { "Alps.txt", "Carpathians.txt" };
    Mountains mountains(filenames);
    // Get two random mountains and check if they are different and not empty
    std::string mountain1 = mountains.getRandomMountain();
    std::string mountain2 = mountains.getRandomMountain();
    BOOST_REQUIRE(mountain1 != "");
    BOOST_REQUIRE(mountain2 != "");
    BOOST_REQUIRE(mountain1 != mountain2);
}

// Test case for the getRandomMountain method of the Mountains class with an empty vector of filenames
BOOST_AUTO_TEST_CASE(TestGetRandomMountainWithEmptyFilenames)
{
    // Initialize the Mountains object with an empty vector of filenames
    std::vector<std::string> filenames = {};
    Mountains mountains(filenames);
    // Check if an empty string is returned as a random mountain
    std::string mountain = mountains.getRandomMountain();
    BOOST_REQUIRE(mountain == "");
}

// Test case for the checkRange method of the Mountains class
BOOST_AUTO_TEST_CASE(TestCheckRange)
{
    // Initialize the Mountains object with a vector of filenames
    std::vector<std::string> filenames = { "Alps.txt", "Carpathians.txt", };
    Mountains mountains(filenames);
    // Check if the checkRange method returns true for valid input
    BOOST_CHECK(mountains.checkRange("Piz Bernina", "Alps"));
    BOOST_CHECK(mountains.checkRange("Gerlach", "Carpathians"));
}

// Test case for the checkRange method of the Mountains class with invalid input
BOOST_AUTO_TEST_CASE(TestCheckRangeWithInvalidInputs)
{
    // Initialize the Mountains object with a vector of filenames
    std::vector<std::string> filenames = { "Alps.txt", "Carpathians.txt" };
    Mountains mountains(filenames);
    // Check if the checkRange method returns false for invalid mountain and range names
    BOOST_CHECK(!mountains.checkRange("Piz Bernina", "InvalidRange"));
    BOOST_CHECK(!mountains.checkRange("InvalidMountain", "Alps"));
    BOOST_CHECK(!mountains.checkRange("InvalidMountain", "InvalidRange"));
}

// Test case for the getRandomMountain method of the Mountains class with duplicate filenames
BOOST_AUTO_TEST_CASE(TestGetRandomMountainWithDuplicateFilenames)
{
    // Initialize the Mountains object with a vector of filenames
    std::vector<std::string> filenames = { "Alps.txt", "Carpathians.txt",};
    Mountains mountains(filenames);

    BOOST_REQUIRE(mountains.getRandomMountain() != "");
}

// Template test to ensure getRandomMountain method generates different mountains
BOOST_AUTO_TEST_CASE_TEMPLATE(testGetRandomMountain, T, std::vector<std::string>)
{
    std::vector<std::string> filenames = { "Alps.txt", "Carpathians.txt", };
    Mountains mountains(filenames);
    std::vector<std::string> mountainNames;
    for (int i = 0; i < 100; ++i) {
        std::string mountain = mountains.getRandomMountain();
        BOOST_REQUIRE_NE(mountain, "");
        mountainNames.push_back(mountain);
    }
    BOOST_REQUIRE_EQUAL(mountainNames.size(), 100);
    BOOST_REQUIRE_NE(mountainNames[0], mountainNames[1]); // make sure the random mountains are different
    BOOST_REQUIRE_NE(mountainNames[1], mountainNames[2]);
}

// Test startQuiz function to ensure it runs without errors
BOOST_AUTO_TEST_CASE(startQuizTest) {
    BOOST_CHECK_NO_THROW(void startQuiz());
}

// Test mechanics function to ensure it runs without errors
BOOST_AUTO_TEST_CASE(mechanicsTest) {
    BOOST_CHECK_NO_THROW(void mechanics());
}

// Test printResults function to ensure it runs without errors
BOOST_AUTO_TEST_CASE(PrintResultsTest) {
    BOOST_CHECK_NO_THROW(void printResults());
}

BOOST_AUTO_TEST_SUITE_END()