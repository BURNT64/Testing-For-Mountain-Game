#include "Mountains.h"
#include <thread>
#include <map>

#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
namespace bdata = boost::unit_test::data;



std::vector<std::string> files = { "Alps.txt", "Carpathians.txt", "Icelandic Highlands.txt", "Pyrenees.txt" };
std::map<std::string, std::vector<std::string> > data = { {"Alps", { "Dom","Olan","Scopi","Piz Bernina","Grivola","Marmolada"}},
															{"Pyrenees",{"Aneto", "Taga", "Monte Perdido", "Pedraforca","Cerbillona", "Espadas Peak"}},
															{"Icelandic Highlands",{"Hekla","Maelifell", "Brennisteinsalda", "Modi", "Magni", "Eyjafjallajokull"}},
															{"Carpathians", {"Rysy","Gerlach","Swinica","Krivan","Mnich"}} };

struct f {
	Mountains m;
	f() : m(files) {}
	~f() {}
};

BOOST_FIXTURE_TEST_SUITE(allTests, f)

BOOST_AUTO_TEST_CASE(seeding)
{
	srand(0);
	std::string a = m.getRandomMountain();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	srand(0);
	std::string b = m.getRandomMountain();
	BOOST_TEST(a == b, "RANDOMNESS CRITERION NOT MET: You should only seed the random number generator once at the beginning of your program");
}

BOOST_AUTO_TEST_CASE(randomness)
{
	srand(0);
	std::string first = m.getRandomMountain();
	int differences = 0;
	for (int i = 0; i < 100; i++)
		if (m.getRandomMountain() != first)
			differences++;
	BOOST_TEST(differences > 70, "RANDOMNESS CRITERION NOT MET: Your random mountains don't appear to be very random");
}

BOOST_AUTO_TEST_CASE(invalidMountain)
{
	BOOST_TEST(!m.checkRange("Dummy", "Alps"), "INVALID STRING INCORRECTLY HANDLED: 'Dummy' is not a mountain.");
}

BOOST_AUTO_TEST_CASE(invalidRange)
{
	BOOST_TEST(!m.checkRange("Rysy", "Dummy"), "INVALID STRING INCORRECTLY HANDLED: 'Dummy' is not a mountain range.");
}

BOOST_DATA_TEST_CASE(allAlps, bdata::make(data["Alps"]), sample)
{
	BOOST_TEST(m.checkRange(sample, "Alps"), "FALSE NEGATIVE: " + sample + " should be in the Alps");
}

BOOST_DATA_TEST_CASE(allCarpathians, bdata::make(data["Carpathians"]), sample)
{
	BOOST_TEST(m.checkRange(sample, "Carpathians"), "FALSE NEGATIVE: " + sample + " should be in the Carpathians");
}

BOOST_DATA_TEST_CASE(allIcelandicHighlands, bdata::make(data["Icelandic Highlands"]), sample)
{
	BOOST_TEST(m.checkRange(sample, "Icelandic Highlands"), "FALSE NEGATIVE: " + sample + " should be in the Icelandic Highlands");
}

BOOST_DATA_TEST_CASE(RandomPyrenees, bdata::make(data["Pyrenees"]), sample)
{
	BOOST_TEST(m.checkRange(sample, "Pyrenees"), "FALSE NEGATIVE: " + sample + " should be in the Pyrenees");
}

BOOST_DATA_TEST_CASE(RandomWrongAnswers, bdata::random(0, 11999) ^ bdata::xrange(50), sample, idx)
{
	std::vector<std::string> names = { "Alps","Carpathians","Icelandic Highlands","Pyrenees" };
	std::string mRange = names[sample / 3000];
	int wPicker = (sample % 3000) / 1000;
	if (wPicker >= (sample / 3000))
		wPicker++;
	std::string wRange = names[wPicker];
	BOOST_TEST(!m.checkRange(data[mRange][sample % data[mRange].size()], wRange), "FALSE POSITIVE: " + data[mRange][sample % data[mRange].size()] + " is not in the " + wRange);
}

BOOST_AUTO_TEST_CASE(noHardcodedStrings)
{
	std::string line, txt;
	
	std::ifstream ifs("Mountains.cpp");
	while (std::getline(ifs, line))
		txt.append(line);
	ifs.close();
	
	ifs.open("Mountains.h");
	while (std::getline(ifs, line))
		txt.append(line);
	ifs.close();

	for(auto i : data)
		for(std::string j : i.second)
			BOOST_TEST(txt.find(j) == std::string::npos, "HARDCODED STRING PRESENT: " + j);
}

BOOST_AUTO_TEST_SUITE_END()