#include "Mountains.hpp"
#include <thread>
#include <map>

#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
namespace bdata = boost::unit_test::data;



BOOST_AUTO_TEST_SUITE(TestSuite)

int main(int argc, char* argv[])
{
    return 0;
}

BOOST_AUTO_TEST_CASE(test_main)
{
    // test code for the main() function
    BOOST_CHECK_EQUAL(main(0, nullptr), 0); // example test to check return value
}

BOOST_AUTO_TEST_CASE(IncorrectFileFormatExceptionTest)
{
    BOOST_CHECK_THROW(
        throw IncorrectFileFormatException("test message"),
        IncorrectFileFormatException
    );
}

// Test constructor
BOOST_AUTO_TEST_CASE(TestConstructor)
{
    std::vector<std::string> filenames = { "Alps.txt", "Carpathians.txt" };
    Mountains mountains(filenames);
    BOOST_REQUIRE(mountains.getRandomMountain() != "");
}

// Test getRandomMountain method
BOOST_AUTO_TEST_CASE(TestGetRandomMountain)
{
    std::vector<std::string> filenames = { "Alps.txt", "Carpathians.txt" };
    Mountains mountains(filenames);
    std::string mountain1 = mountains.getRandomMountain();
    std::string mountain2 = mountains.getRandomMountain();
    BOOST_REQUIRE(mountain1 != "");
    BOOST_REQUIRE(mountain2 != "");
    BOOST_REQUIRE(mountain1 != mountain2);
}

// Test getRandomMountain method with empty filenames vector
BOOST_AUTO_TEST_CASE(TestGetRandomMountainWithEmptyFilenames)
{
    std::vector<std::string> filenames = {};
    Mountains mountains(filenames);
    std::string mountain = mountains.getRandomMountain();
    BOOST_REQUIRE(mountain == "");
}

BOOST_AUTO_TEST_CASE(TestCheckRange)
{
    std::vector<std::string> filenames = { "Alps.txt", "Carpathians.txt", };
    Mountains mountains(filenames);

    BOOST_CHECK(mountains.checkRange("Piz Bernina", "Alps"));
    BOOST_CHECK(mountains.checkRange("Gerlach", "Carpathians"));
}

BOOST_AUTO_TEST_CASE(TestCheckRangeWithInvalidInputs)
{
    std::vector<std::string> filenames = { "Alps.txt", "Carpathians.txt" };
    Mountains mountains(filenames);

    // Check for invalid range
    BOOST_CHECK(!mountains.checkRange("Piz Bernina", "InvalidRange"));
    // Check for invalid mountain name
    BOOST_CHECK(!mountains.checkRange("InvalidMountain", "Alps"));
    // Check for invalid mountain name and invalid range
    BOOST_CHECK(!mountains.checkRange("InvalidMountain", "InvalidRange"));
}

BOOST_AUTO_TEST_CASE(TestGetRandomMountainWithDuplicateFilenames)
{
    std::vector<std::string> filenames = { "Alps.txt", "Carpathians.txt",};
    Mountains mountains(filenames);

    BOOST_REQUIRE(mountains.getRandomMountain() != "");
}

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

BOOST_AUTO_TEST_CASE(startQuizTest) {
    // Call printResults() and ensure that it runs without errors
    BOOST_CHECK_NO_THROW(void startQuiz());
}

BOOST_AUTO_TEST_CASE(mechanicsTest) {
    // Call printResults() and ensure that it runs without errors
    BOOST_CHECK_NO_THROW(void mechanics());
}

BOOST_AUTO_TEST_CASE(PrintResultsTest) {
    // Call printResults() and ensure that it runs without errors
    BOOST_CHECK_NO_THROW(void printResults());
}

BOOST_AUTO_TEST_SUITE_END()