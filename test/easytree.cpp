#include <catch.hpp>

#include <algorithm>

#include <easytree/tree>
#include <easytree/breadth_first>
#include <easytree/depth_first>

SCENARIO("TDD") {
  using namespace easytree;
  WHEN("Non-const tree") {
    auto tree =
      node<int>(1) << node<int>(2)
                   << node<int>(3)
                   << node<int>(4)
                   << (node<int>(5)
                       << node<int>(6)
                       << node<int>(7))
                   << (node<int>(8)
                       << (node<int>(9)
                           << node<int>(10)
                           << node<int>(11))
                       << node<int>(12));

    THEN("Test breadth-first") {
      std::vector<int> actual;
      for (auto& v : breadth_first<int>(tree)) {
        actual.push_back(**v);
      }
      std::vector<int> expected{1, 2, 3, 4, 5, 8, 6, 7, 9, 12, 10, 11};
      REQUIRE(actual == expected);

      THEN("Test levels") {
        std::vector<int> actual;
        std::vector<int> expected{0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3};
        for (auto it = breadth_first<int>(tree).begin();
             it != breadth_first<int>(tree).end(); ++it) {
          actual.push_back(it.level());
        }
        REQUIRE(actual == expected);
      }

      THEN("Test STL find_if") {
        auto actual = std::find_if(breadth_first<int>(tree).begin(),
                                   breadth_first<int>(tree).end(),
                                   [] (const decltype(tree)& n) {
                                     return **n == 11;
                                   });
        REQUIRE(actual != breadth_first<int>(tree).end());
        REQUIRE(actual.level() == 3);
      }
    }

    THEN("Test depth-first") {
      std::vector<int> actual;
      for (auto& v : depth_first<int>(tree)) {
        actual.push_back(**v);
      }
      std::vector<int> expected{1, 8, 12, 9, 11, 10, 5, 7, 6, 4, 3, 2};
      REQUIRE(actual == expected);

      THEN("Test levels") {
        std::vector<int> actual;
        std::vector<int> expected{0, 1, 2, 2, 3, 3, 1, 2, 2, 1, 1, 1};
        for (auto it = depth_first<int>(tree).begin();
             it != depth_first<int>(tree).end(); ++it) {
          actual.push_back(it.level());
        }
        REQUIRE(actual == expected);
      }

      THEN("Test STL find_if") {
        auto actual = std::find_if(depth_first<int>(tree).begin(),
                                   depth_first<int>(tree).end(),
                                   [] (const decltype(tree)& n) {
                                     return **n == 11;
                                   });
        REQUIRE(actual != depth_first<int>(tree).end());
        REQUIRE(actual.level() == 3);
      }
    }

    THEN("Test depth <--> breadth iterator conversion") {
      for (auto b = breadth_first<int>(tree).begin();
           b != breadth_first<int>(tree).end(); ++b) {
        auto d = b.depth_first_iterator();
        REQUIRE(*b == *d);
      }
      for (auto d = depth_first<int>(tree).begin();
           d != depth_first<int>(tree).end(); ++d) {
        auto b = d.breadth_first_iterator();
        REQUIRE(*b == *d);
      }
    }
  }
  
  WHEN("Const tree") {
    const auto tree =
      node<int>(1) << node<int>(2)
                   << node<int>(3)
                   << node<int>(4)
                   << (node<int>(5)
                       << node<int>(6)
                       << node<int>(7))
                   << (node<int>(8)
                       << (node<int>(9)
                           << node<int>(10)
                           << node<int>(11))
                       << node<int>(12));

    THEN("Test breadth-first") {
      std::vector<int> actual;
      for (const auto& v : breadth_first<int>(tree)) {
        actual.push_back(**v);
      }
      std::vector<int> expected{1, 2, 3, 4, 5, 8, 6, 7, 9, 12, 10, 11};
      REQUIRE(actual == expected);

      THEN("Test levels") {
        std::vector<int> actual;
        std::vector<int> expected{0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3};
        for (auto it = breadth_first<int>(tree).cbegin();
             it != breadth_first<int>(tree).cend(); ++it) {
          actual.push_back(it.level());
        }
        REQUIRE(actual == expected);
      }

      THEN("Test STL find_if") {
        auto actual = std::find_if(breadth_first<int>(tree).cbegin(),
                                   breadth_first<int>(tree).cend(),
                                   [] (const decltype(tree)& n) {
                                     return **n == 11;
                                   });
        REQUIRE(actual != breadth_first<int>(tree).cend());
        REQUIRE(actual.level() == 3);
      }
    }

    THEN("Test depth-first") {
      std::vector<int> actual;
      for (const auto& v : depth_first<int>(tree)) {
        actual.push_back(**v);
      }
      std::vector<int> expected{1, 8, 12, 9, 11, 10, 5, 7, 6, 4, 3, 2};
      REQUIRE(actual == expected);

      THEN("Test levels") {
        std::vector<int> actual;
        std::vector<int> expected{0, 1, 2, 2, 3, 3, 1, 2, 2, 1, 1, 1};
        for (auto it = depth_first<int>(tree).cbegin();
             it != depth_first<int>(tree).cend(); ++it) {
          actual.push_back(it.level());
        }
        REQUIRE(actual == expected);
      }

      THEN("Test STL find_if") {
        auto actual = std::find_if(depth_first<int>(tree).cbegin(),
                                   depth_first<int>(tree).cend(),
                                   [] (const decltype(tree)& n) {
                                     return **n == 11;
                                   });
        REQUIRE(actual != depth_first<int>(tree).cend());
        REQUIRE(actual.level() == 3);
      }
    }

    THEN("Test depth <--> breadth iterator conversion") {
      for (auto b = breadth_first<int>(tree).cbegin();
           b != breadth_first<int>(tree).cend(); ++b) {
        auto d = b.depth_first_iterator();
        REQUIRE(*b == *d);
      }
      for (auto d = depth_first<int>(tree).cbegin();
           d != depth_first<int>(tree).cend(); ++d) {
        auto b = d.breadth_first_iterator();
        REQUIRE(*b == *d);
      }
    }
  }
}
