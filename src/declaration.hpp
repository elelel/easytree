#pragma once

#include <memory>
#include <queue>
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
  
  // Create subnode
  template <typename T>
  std::shared_ptr<tree::node<T>> operator<<(std::shared_ptr<tree::node<T>> lhs,
                                             const std::shared_ptr<tree::node<T>>& rhs);
  // Create same level node
  template <typename T>
  std::shared_ptr<tree::node<T>> operator|(std::shared_ptr<tree::node<T>> lhs,
                                            const std::shared_ptr<tree::node<T>>& rhs);
  namespace view {
    template <typename Node>
    struct breadth_first;
    template <typename T>
    struct breadth_first_iterator;
    template <typename T>
    struct const_breadth_first_iterator;
  }
}

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
      // Create same level node
      friend std::shared_ptr<tree::node<T>> operator|<T>(std::shared_ptr<tree::node<T>> lhs,
                                                        const std::shared_ptr<tree::node<T>>& rhs);
      
      friend struct view::breadth_first<type>;
      friend struct view::breadth_first_iterator<type>;
      friend struct view::const_breadth_first_iterator<type>;

      node();
      node(T value);
      // Add child if doesn't exist
      void add_child(const type_ptr& rhs);
      reference operator*();
      
    private:
      value_type value_;
      type_ptr parent_;
      std::vector<type_ptr> children_;
    };
  }

  namespace view {
    template <typename Node>
    struct breadth_first {
      using iterator = breadth_first_iterator<Node>;
      using const_iterator = const_breadth_first_iterator<const Node>;

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
      breadth_first_iterator(type&& other);
      void swap(type& other);
      type& operator=(const type& other);

      bool operator==(const type& other) const;
      bool operator!=(const type& other) const;

      type& operator++();

      reference operator*();
      size_t level() const;

    private:
      std::queue<std::tuple<typename Node::type_ptr, size_t>> q_;
    };
    
    template <typename T>
    struct const_breadth_first_iterator {
    };
  }

  template <typename T>
  view::breadth_first<tree::node<T>> breadth_first(typename tree::node<T>::type_ptr n);

}
