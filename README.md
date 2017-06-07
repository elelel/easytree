# EasyTree
Simple STL-compatible tree implementation. 

Place the files to a location in your project where you can #include them

## Create tree
```
#include <easytree/tree>
// ...
    using namespace easytree;
    auto tree =
      node<std::string>("Root") << node<std::string>("Child")
                                << node<std::string>("Another child")
                                << (node<std::string>("Child with subchildren")
                                    << node<std::string>("Subchild 1")
                                    << node<std::string>("Subchild 2"));
// ...      
```

## Walk breadth-first
```
#include <eastytree/breadth_first>
// ...
using namespace easytree;
for (const auto& s : breadth_first<std::string>(tree)) {
  std::cout << s << "\n"
}
// ...
```

