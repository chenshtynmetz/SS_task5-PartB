/*
 *
 * AUTHORS: chen
 * 
 * Date: 2022-05
 */

#include "doctest.h"
#include "OrgChart.hpp"
#include <vector>
using namespace ariel;

#include <string>
#include <algorithm>

TEST_CASE("check level order") {
	OrgChart org;
    CHECK_NOTHROW(org.add_root("CEO")); 
    CHECK("CEO" == *(org.begin_level_order()));
    CHECK_NOTHROW(org.add_sub("CEO","CTO"));
    CHECK("CEO" == *org.begin_level_order());
    CHECK_NOTHROW(org.add_sub("CTO", "emp1"));
    CHECK("CEO" == *(org.begin_level_order()));
    CHECK_NOTHROW(org.add_sub("CEO", "CFO"));
    CHECK("CEO" == *(org.begin_level_order()));
    CHECK_NOTHROW(org.add_root("new_ceo"));
    CHECK("new_ceo" == *(org.begin_level_order()));
    CHECK_NOTHROW(org.add_sub("CFO", "emp2"));
    CHECK("new_ceo" == *(org.begin_level_order()));
    CHECK_NOTHROW(org.add_sub("new_ceo", "COO"));
    CHECK("new_ceo" == *(org.begin_level_order()));
}

TEST_CASE("check reverse order") {
    OrgChart org;
    CHECK_NOTHROW(org.add_root("CEO"));
    CHECK("CEO" == *(org.begin_reverse_order()));
    CHECK_NOTHROW(org.add_sub("CEO","CTO"));
    CHECK("CTO" == *(org.begin_reverse_order())); 
    CHECK_NOTHROW(org.add_sub("CTO", "emp1"));
    CHECK("emp1" == *(org.begin_reverse_order()));
    CHECK_NOTHROW(org.add_sub("CEO", "CFO"));
    CHECK("emp1" == *(org.begin_reverse_order()));
    CHECK_NOTHROW(org.add_root("new_ceo"));
    CHECK("emp1" == *(org.begin_reverse_order()));
    CHECK_NOTHROW(org.add_sub("CFO", "emp2"));
    CHECK("emp1" == *(org.begin_reverse_order()));
    CHECK_NOTHROW(org.add_sub("new_ceo", "COO"));
    CHECK("emp1" == *(org.begin_reverse_order()));
}

TEST_CASE("check preorder") {
    OrgChart org;
    CHECK_NOTHROW(org.add_root("CEO"));
    CHECK("CEO" == *(org.begin_preorder()));
    CHECK_NOTHROW(org.add_sub("CEO","CTO"));
    CHECK("CEO" == *(org.begin_preorder())); 
    CHECK_NOTHROW(org.add_sub("CTO", "emp1"));
    CHECK("CEO" == *(org.begin_preorder()));
    CHECK_NOTHROW(org.add_sub("CEO", "CFO"));
    CHECK("CEO" == *(org.begin_preorder()));
    CHECK_NOTHROW(org.add_root("new_ceo"));
    CHECK("new_ceo" == *(org.begin_preorder()));
    CHECK_NOTHROW(org.add_sub("CFO", "emp2"));
    CHECK("new_ceo" == *(org.begin_preorder()));
    CHECK_NOTHROW(org.add_sub("new_ceo", "COO"));
    CHECK("new_ceo" == *(org.begin_preorder()));
}

TEST_CASE("Bad input"){
    OrgChart org;
    CHECK_THROWS(org.add_sub("A", "aa"));
    CHECK_THROWS(org.add_sub("B", "aa"));
    CHECK_NOTHROW(org.add_root("CEO"));
    CHECK_THROWS(org.add_sub("CTO", "CEO1"));
    CHECK_THROWS(org.add_sub("emp1", "CEO1"));
}