#pragma once

#include <algorithm>

#include "declaration.hpp"

namespace easytree {
  namespace view {
    template <typename Node>
    depth_first<Node>::depth_first(typename Node::type_ptr n) :
      n_(n) {
    }

    template <typename Node>
    auto depth_first<Node>::begin() -> iterator {
      return iterator(n_);
    }
    
    template <typename Node>
    auto depth_first<Node>::begin() const -> const_iterator {
      return const_iterator(n_);
    }
    
    template <typename Node>
    auto depth_first<Node>::cbegin() const -> const_iterator {
      return const_iterator(n_);
    }
    
    template <typename Node>
    auto depth_first<Node>::end() -> iterator {
      return iterator();
    }
    
    template <typename Node> 
    auto depth_first<Node>::end() const -> const_iterator {
      return const_iterator();
    }
    
    template <typename Node>
    auto depth_first<Node>::cend() const -> const_iterator {
      return const_iterator();
    }

    template <typename Node>
    depth_first_iterator<Node>::depth_first_iterator() {
    }

    template <typename Node>
    depth_first_iterator<Node>::depth_first_iterator(typename Node::type_ptr n) {
      q_.push({n, 0});
    }
  
    template <typename Node>
    depth_first_iterator<Node>::depth_first_iterator(const type& other) :
      q_(other.q_) {
    }

    template <typename Node>
    depth_first_iterator<Node>::depth_first_iterator(const view::breadth_first_iterator<Node>& other) {
      q_.push({*other, other.level()});
    }
  
    template <typename Node>
    depth_first_iterator<Node>::depth_first_iterator(type&& other) :
      q_(std::move(other.q_)) {
    }

    template <typename Node>
    auto depth_first_iterator<Node>::breadth_first_iterator() -> view::breadth_first_iterator<Node> {
      return view::breadth_first_iterator<Node>(*this);
    }
    
    template <typename Node>
    void depth_first_iterator<Node>::swap(type& other) {
      std::swap(q_, other.q_);
    }
  
    template <typename Node>
    auto depth_first_iterator<Node>::operator=(const type& other) -> type& {
      type tmp(other);
      swap(tmp);
      return *this;
    }

    template <typename Node>
    bool depth_first_iterator<Node>::operator==(const type& other) const {
      return q_ == other.q_;
    }
  
    template <typename Node>
    bool depth_first_iterator<Node>::operator!=(const type& other) const {
      return !(*this == other);
    }

    template <typename Node>
    auto depth_first_iterator<Node>::operator*() -> reference {
      return std::get<0>(q_.top());
    }

    template <typename Node>
    auto depth_first_iterator<Node>::operator*() const -> value_type {
      return std::get<0>(q_.top());
    }
    
    template <typename Node>
    size_t depth_first_iterator<Node>::level() const {
      return std::get<1>(q_.top());
    }
    
    template <typename Node>
    auto depth_first_iterator<Node>::operator++() -> type& {
      if (q_.size() != 0) {
        auto v = q_.top();
        q_.pop();
        for (auto& c : std::get<0>(v)->children_)
          q_.push({c, std::get<1>(v) + 1});
      }
      return *this;
    }
  }
  
  template <typename T>
  view::depth_first<tree::node<T>> depth_first(typename tree::node<T>::type_ptr n) {
    return view::depth_first<tree::node<T>>(n);
  }  
}
