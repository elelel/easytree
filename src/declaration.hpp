#pragma once

#include <memory>
#include <queue>
#include <stack>
#include <tuple>
#include <vector>

// Predeclare
namespace easytree {
  namespace tree {
    template <typename T>
    struct node;
  }
  
  template <typename T>
  std::shared_ptr<tree::node<T>> node();
  
  template <typename T>
  std::shared_ptr<tree::node<T>> node(T value);
  
  namespace view {
    template <typename Node>
    struct breadth_first;
    template <typename T>
    struct breadth_first_iterator;
    template <typename T>
    struct const_breadth_first_iterator;
    template <typename Node>
    struct depth_first;
    template <typename T>
    struct depth_first_iterator;
    template <typename T>
    struct const_depth_first_iterator;
  }
}
// Create subnode
template <typename T>
std::shared_ptr<easytree::tree::node<T>> operator<<(std::shared_ptr<easytree::tree::node<T>> lhs,
                                                    const std::shared_ptr<easytree::tree::node<T>>& rhs);


// Declare
namespace easytree {
  namespace tree {
    template <typename T>
    struct node : std::enable_shared_from_this<node<T>> {
      using value_type = T;
      using reference = value_type&;
      using type = node<value_type>;
      using type_ptr = std::shared_ptr<type>;

      // Create subnode
      friend std::shared_ptr<tree::node<T>> operator<<<T>(std::shared_ptr<tree::node<T>> lhs,
                                                         const std::shared_ptr<tree::node<T>>& rhs);
      friend struct view::breadth_first<type>;
      friend struct view::breadth_first_iterator<type>;
      friend struct view::const_breadth_first_iterator<type>;
      friend struct view::depth_first<type>;
      friend struct view::depth_first_iterator<type>;
      friend struct view::const_depth_first_iterator<type>;

      node();
      // Construct node with value
      node(T value);
      
      // Add child if doesn't exist
      void add_child(const type_ptr& rhs);
      reference operator*();

      const std::vector<type_ptr>& children() const;
    private:
      value_type value_;
      //      type_ptr parent_;
      std::vector<type_ptr> children_;
    };
  }

  namespace view {
    template <typename Node>
    struct breadth_first {
      using iterator = breadth_first_iterator<Node>;
      // TODO: Write specialized const iterator, returning const&
      using const_iterator = breadth_first_iterator<const Node>;

      iterator begin();
      const_iterator begin() const;
      const_iterator cbegin() const;
      iterator end();
      const_iterator end() const;
      const_iterator cend() const;

      breadth_first(typename Node::type_ptr n);
    private:
      typename Node::type_ptr n_;
    };

    template <typename Node>
    struct breadth_first_iterator {
      using type = breadth_first_iterator<Node>;
      using iterator_category = std::forward_iterator_tag;
      using value_type = typename Node::type_ptr;
      using reference = value_type&;
      using pointer = value_type*;
      using difference_type = ptrdiff_t;

      breadth_first_iterator();
      breadth_first_iterator(typename Node::type_ptr);
      breadth_first_iterator(const type& other);
      breadth_first_iterator(const depth_first_iterator<Node>& other);
      breadth_first_iterator(type&& other);
      auto depth_first_iterator() -> depth_first_iterator<Node>;
      void swap(type& other);
      type& operator=(const type& other);

      bool operator==(const type& other) const;
      bool operator!=(const type& other) const;

      type& operator++();

      reference operator*();
      // Return current node's tree level
      size_t level() const;

    private:
      std::queue<std::tuple<typename Node::type_ptr, size_t>> q_;
    };

    template <typename Node>
    struct depth_first {
      using iterator = depth_first_iterator<Node>;
      using const_iterator = const_depth_first_iterator<const Node>;

      iterator begin();
      const_iterator begin() const;
      const_iterator cbegin() const;
      iterator end();
      const_iterator end() const;
      const_iterator cend() const;

      depth_first(typename Node::type_ptr n);
    private:
      typename Node::type_ptr n_;

    };

    template <typename Node>
    struct depth_first_iterator {
      using type = depth_first_iterator<Node>;
      using iterator_category = std::forward_iterator_tag;
      using value_type = typename Node::type_ptr;
      using reference = value_type&;
      using pointer = value_type*;
      using difference_type = ptrdiff_t;

      depth_first_iterator();
      depth_first_iterator(typename Node::type_ptr);
      depth_first_iterator(const type& other);
      depth_first_iterator(const breadth_first_iterator<Node>& other);
      depth_first_iterator(type&& other);
      auto breadth_first_iterator() -> breadth_first_iterator<Node>;
      void swap(type& other);
      type& operator=(const type& other);

      bool operator==(const type& other) const;
      bool operator!=(const type& other) const;

      type& operator++();

      reference operator*();
      // Return current node's tree level
      size_t level() const;

    private:
      std::stack<std::tuple<typename Node::type_ptr, size_t>> q_;
    };
    
  }

  template <typename T>
  view::breadth_first<tree::node<T>> breadth_first(typename tree::node<T>::type_ptr n);
  template <typename T>
  view::depth_first<tree::node<T>> depth_first(typename tree::node<T>::type_ptr n);

}
