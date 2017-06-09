#pragma once

#include <algorithm>

#include "declaration.hpp"

namespace easytree {
  namespace view {
    template <typename Node>
    breadth_first<Node>::breadth_first(typename Node::type_ptr n) :
      n_(n) {
    }

    template <typename Node>
    auto breadth_first<Node>::begin() -> iterator {
      return iterator(n_);
    }
    
    template <typename Node>
    auto breadth_first<Node>::begin() const -> const_iterator {
      return const_iterator(n_);
    }
    
    template <typename Node>
    auto breadth_first<Node>::cbegin() const -> const_iterator {
      return const_iterator(n_);
    }
    
    template <typename Node>
    auto breadth_first<Node>::end() -> iterator {
      return iterator();
    }
    
    template <typename Node> 
    auto breadth_first<Node>::end() const -> const_iterator {
      return const_iterator();
    }
    
    template <typename Node>
    auto breadth_first<Node>::cend() const -> const_iterator {
      return const_iterator();
    }
    
    template <typename Node>
    breadth_first_iterator<Node>::breadth_first_iterator() {
    }
    
    template <typename Node>
    breadth_first_iterator<Node>::breadth_first_iterator(typename Node::type_ptr n) {
      q_.push({n, 0});
    }
  
    template <typename Node>
    breadth_first_iterator<Node>::breadth_first_iterator(const type& other) :
      q_(other.q_) {
    }
  
    template <typename Node>
    breadth_first_iterator<Node>::breadth_first_iterator(const view::depth_first_iterator<Node>& other) {
      q_.push({*other, other.level()});
    }
    
    template <typename Node>
    breadth_first_iterator<Node>::breadth_first_iterator(type&& other) :
      q_(std::move(other.q_)) {
    }

    template <typename Node>
    auto breadth_first_iterator<Node>::depth_first_iterator() -> view::depth_first_iterator<Node> {
      return view::depth_first_iterator<Node>(*this);
    }
  
    template <typename Node>
    void breadth_first_iterator<Node>::swap(type& other) {
      std::swap(q_, other.q_);
    }
  
    template <typename Node>
    auto breadth_first_iterator<Node>::operator=(const type& other) -> type& {
      type tmp(other);
      swap(tmp);
      return *this;
    }

    template <typename Node>
    bool breadth_first_iterator<Node>::operator==(const type& other) const {
      if ((q_.size() == 0) && (other.q_.size() == 0)) return true;
      if ((q_.size() != 0) && (other.q_.size() != 0)) 
        return q_.front() == other.q_.front();
      return false;
    }
  
    template <typename Node>
    bool breadth_first_iterator<Node>::operator!=(const type& other) const {
      return !(*this == other);
    }

    template <typename Node>
    auto breadth_first_iterator<Node>::operator*() -> reference {
      return std::get<0>(q_.front());
    }

    template <typename Node>
    auto breadth_first_iterator<Node>::operator*() const -> const value_type {
      return std::get<0>(q_.front());
    }

    template <typename Node>
    size_t breadth_first_iterator<Node>::level() const {
      return std::get<1>(q_.front());
    }
    
    template <typename Node>
    auto breadth_first_iterator<Node>::operator++() -> type& {
      if (q_.size() != 0) {
        for (auto& c : std::get<0>(q_.front())->children_)
          q_.push({c, std::get<1>(q_.front()) + 1});
        q_.pop();
      }
      return *this;
    }
    
    template <typename Node>
    const_breadth_first_iterator<Node>::const_breadth_first_iterator() {
    }
    
    template <typename Node>
    const_breadth_first_iterator<Node>::const_breadth_first_iterator(typename Node::type_ptr n) {
      q_.push({n, 0});
    }
  
    template <typename Node>
    const_breadth_first_iterator<Node>::const_breadth_first_iterator(const type& other) :
      q_(other.q_) {
    }
  
    template <typename Node>
    const_breadth_first_iterator<Node>::const_breadth_first_iterator(const view::const_depth_first_iterator<Node>& other) {
      q_.push({*other, other.level()});
    }
    
    template <typename Node>
    const_breadth_first_iterator<Node>::const_breadth_first_iterator(type&& other) :
      q_(std::move(other.q_)) {
    }

    template <typename Node>
    auto const_breadth_first_iterator<Node>::depth_first_iterator() -> view::const_depth_first_iterator<Node> {
      return view::const_depth_first_iterator<Node>(*this);
    }
  
    template <typename Node>
    void const_breadth_first_iterator<Node>::swap(type& other) {
      std::swap(q_, other.q_);
    }
  
    template <typename Node>
    auto const_breadth_first_iterator<Node>::operator=(const type& other) -> type& {
      type tmp(other);
      swap(tmp);
      return *this;
    }

    template <typename Node>
    bool const_breadth_first_iterator<Node>::operator==(const type& other) const {
      if ((q_.size() == 0) && (other.q_.size() == 0)) return true;
      if ((q_.size() != 0) && (other.q_.size() != 0)) 
        return q_.front() == other.q_.front();
      return false;
    }
  
    template <typename Node>
    bool const_breadth_first_iterator<Node>::operator!=(const type& other) const {
      return !(*this == other);
    }

    template <typename Node>
    auto const_breadth_first_iterator<Node>::operator*() const -> const reference {
      return std::get<0>(q_.front());
    }

    template <typename Node>
    size_t const_breadth_first_iterator<Node>::level() const {
      return std::get<1>(q_.front());
    }
    
    template <typename Node>
    auto const_breadth_first_iterator<Node>::operator++() -> type& {
      if (q_.size() != 0) {
        for (auto& c : std::get<0>(q_.front())->children_)
          q_.push({c, std::get<1>(q_.front()) + 1});
        q_.pop();
      }
      return *this;
    }
  }
  
  template <typename T>
  view::breadth_first<tree::node<T>> breadth_first(typename tree::node<T>::type_ptr n) {
    return view::breadth_first<tree::node<T>>(n);
  }
  
}
