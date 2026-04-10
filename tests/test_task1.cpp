#include "doctest/doctest.h"
#include "src/VectorStore.h"
#include "src/TestHelper.h"
#include "src/utils.h"
#include <string>
#include <sstream>
#include <vector>
using namespace std;

TEST_CASE("test_1001")
{
    ArrayList<int> arr;
    CHECK(arr.empty() == true);
    CHECK(arr.size() == 0);
    CHECK(TestHelper::getCapacity(arr) == 10);
    CHECK(TestHelper::getCount(arr) == 0);
    CHECK(TestHelper::getData(arr) != nullptr);
}

TEST_CASE("test_1002")
{
    ArrayList<int> arr(5);
    CHECK(arr.empty() == true);
    CHECK(arr.size() == 0);
    CHECK(TestHelper::getCapacity(arr) == 5);
}

TEST_CASE("test_1003")
{
    ArrayList<int> arr(0);
    CHECK(arr.empty() == true);
    CHECK(arr.size() == 0);
    CHECK(TestHelper::getCapacity(arr) == 0);
}

TEST_CASE("test_1004")
{
    ArrayList<int> arr(-5);
    CHECK(arr.empty() == true);
    CHECK(arr.size() == 0);
    CHECK(TestHelper::getCapacity(arr) == -5);
}
