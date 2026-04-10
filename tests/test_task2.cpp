#include "doctest/doctest.h"
#include "src/VectorStore.h"
#include "src/utils.h"
#include "src/TestHelper.h"
#include <string>
#include <vector>

TEST_CASE("test_2001")
{
    SUBCASE("Default constructor and empty list")
    {
        SinglyLinkedList<int> list;
        CHECK(list.empty() == true);
        CHECK(list.size() == 0);
        CHECK(list.toString(int2str) == "");
    }

    SUBCASE("Add elements to the end")
    {
        SinglyLinkedList<int> list;
        list.add(10);
        list.add(20);
        list.add(30);
        CHECK(list.size() == 3);
        CHECK(list.empty() == false);
        CHECK(list.toString(int2str) == "[10]->[20]->[30]");
    }
}

TEST_CASE("test_2002")
{
    SinglyLinkedList<int> list;
    list.add(10);
    list.add(30);

    SUBCASE("Add at beginning (index 0)")
    {
        list.add(0, 5);
        CHECK(list.size() == 3);
        CHECK(list.toString(int2str) == "[5]->[10]->[30]");
    }

    SUBCASE("Add at end (index == size)")
    {
        SinglyLinkedList<int> newList;
        newList.add(10);
        newList.add(30);
        newList.add(2, 20);
        CHECK(newList.size() == 3);
        CHECK(newList.toString(int2str) == "[10]->[30]->[20]");
    }

    SUBCASE("Add in middle")
    {
        SinglyLinkedList<int> midList;
        midList.add(10);
        midList.add(30);
        midList.add(1, 20);
        CHECK(midList.size() == 3);
        CHECK(midList.toString(int2str) == "[10]->[20]->[30]");
    }

    SUBCASE("Add to empty list at index 0")
    {
        SinglyLinkedList<int> emptyList;
        emptyList.add(0, 42);
        CHECK(emptyList.size() == 1);
        CHECK(emptyList.toString(int2str) == "[42]");
    }
}
