#pragma once

#include "declaration.hpp"

namespace easytree {
  namespace tree {
    template <typename T>
    node<T>::node() {
    }

    template <typename T>
    node<T>::node(T value) :
      value_(value) {
    }

    template <typename T>
    void node<T>::add_child(const type_ptr& rhs) {
      if (std::find(children_.begin(), children_.end(), rhs) == children_.end()) {
        children_.push_back(rhs);
      }
    }

    template <typename T>
    auto node<T>::operator*() -> reference {
      return value_;
    }

    template <typename T>
    auto node<T>::children() const -> const std::vector<type_ptr>& {
      return children_;
    }
    
  }

  template <typename T>
  std::shared_ptr<tree::node<T>> node() {
    return std::make_shared<tree::node<T>>();
  }
  
  template <typename T>
  std::shared_ptr<tree::node<T>> node(T value) {
    return std::make_shared<tree::node<T>>(value);
  }

  template <typename T>
  std::shared_ptr<tree::node<T>> operator<<(std::shared_ptr<tree::node<T>> lhs,
                                             const std::shared_ptr<tree::node<T>>& rhs) {
    lhs->add_child(rhs);
    return lhs;
  }

}
