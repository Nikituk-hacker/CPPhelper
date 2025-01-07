const long long __very_big_number = (long long)1e17;
namespace Handmade {
  // Описание Node сначала изменения потом значение \
     например Присвоение__Сумма

  template<typename Info, typename Value>
  struct DynamicSegtree {
    struct Node {
      Value value = {};
      Node *left = 0, *right = 0;
    };
    
    void make_node(Node *&ptr) {
      if (!ptr) ptr = new Node();
    }
    
    long long n;
    Node *root = 0;
    
    DynamicSegtree() : n(0) {}
    
    DynamicSegtree(long long _n) : n(_n) {}
    
    template<typename T>
    DynamicSegtree(const vector<T> &data) {
      n = (long long)data.size();
      std::function<void(long long, long long, Node *&)> build = [&](long long lx, long long rx, Node *&ptr) {
        make_node(ptr);
        if (rx - lx == 1) {
          ptr->value = data[lx];
          return;
        }
        long long m = (lx + rx) / 2;
        build(lx, m, ptr->left);
        build(m, rx, ptr->right);
        ptr->value = ptr->left->value + ptr->right->value;
      };
      build(0, n, root);
    }
    
    void point_set(long long i, Info val) {
      point_set(i, val, 0, n, root);
    }
    
    void point_set(long long i, Info val, long long lx, long long rx, Node *&ptr) {
      make_node(ptr);
      if (rx - lx == 1) {
        ptr->value = val;
        return;
      }
      make_node(ptr->left);
      make_node(ptr->right);
      Value::push(ptr, lx, rx);
      long long m = (lx + rx) / 2;
      if (i < m) point_set(i, val, lx, m, ptr->left);
      else point_set(i, val, m, rx, ptr->right);
      ptr->value = ptr->left->value + ptr->right->value;
    }
    
    void update_range(long long lq, long long rq, Info val) {
      update_range(lq, rq, val, 0, n, root);
    }
    
    void update_range(long long lq, long long rq, Info val, long long lx, long long rx, Node *&ptr) {
      make_node(ptr);
      if (rx <= lq || lx >= rq) return;
      if (lq <= lx && rx <= rq) {
        Value::apply(ptr, val, lx, rx);
        return;
      }
      make_node(ptr->left);
      make_node(ptr->right);
      Value::push(ptr, lx, rx);
      long long m = (lx + rx) / 2;
      update_range(lq, rq, val, lx, m, ptr->left);
      update_range(lq, rq, val, m, rx, ptr->right);
      ptr->value = ptr->left->value + ptr->right->value;
    }
    
    Value get_range(long long lq, long long rq) {
      return get_range(lq, rq, 0, n, root);
    }
    
    Value get_range(long long lq, long long rq, long long lx, long long rx, Node *&ptr) {
      make_node(ptr);
      if (rx <= lq || lx >= rq) return Value();
      if (lq <= lx && rx <= rq) return ptr->value;
      make_node(ptr->left);
      make_node(ptr->right);
      Value::push(ptr, lx, rx);
      long long m = (lx + rx) / 2;
      auto left = get_range(lq, rq, lx, m, ptr->left);
      auto right = get_range(lq, rq, m, rx, ptr->right);
      ptr->value = ptr->left->value + ptr->right->value;
      return left + right;
    }
  };

  struct Set__Max {
    long long mx, av;
    
    Set__Max() : mx(-__very_big_number), av(__very_big_number) {}
    
    Set__Max(ll x) : mx(x), av(__very_big_number) {}
    
    template<typename Node>
    static void apply(Node *n, long long val, long long lx, long long rx) {
      n->value.mx = val;
      n->value.av = val;
    }
    
    template<typename Node>
    static void push(Node *n, long long lx, long long rx) {
      if (n->value.av != __very_big_number) {
        long long m = (lx + rx) / 2;
        apply(n->left, n->value.av, lx, m);
        apply(n->right, n->value.av, m, rx);
        n->value.av = __very_big_number;
      }
    }
    
    Set__Max operator+ (Set__Max n) {
      Set__Max ans;
      ans.mx = max(mx, n.mx);
      return ans;
    }
  };

  struct Set__Min {
    long long mn, av;
    
    Set__Min() : mn(__very_big_number), av(__very_big_number) {}
    
    Set__Min(ll x) : mn(x), av(__very_big_number) {}
    
    template<typename Node>
    static void apply(Node *n, long long val, long long lx, long long rx) {
      n->value.mn = val;
      n->value.av = val;
    }
    
    template<typename Node>
    static void push(Node *n, long long lx, long long rx) {
      if (n->value.av != __very_big_number) {
        long long m = (lx + rx) / 2;
        apply(n->left, n->value.av, lx, m);
        apply(n->right, n->value.av, m, rx);
        n->value.av = __very_big_number;
      }
    }
    
    Set__Min operator+ (Set__Min n) {
      Set__Min ans;
      ans.mn = min(mn, n.mn);
      return ans;
    }
  };

  struct Set__Sum {
    long long sum, av;
    
    Set__Sum() : sum(0), av(__very_big_number) {}
    
    Set__Sum(ll s) : sum(s), av(__very_big_number) {}
    
    template<typename Node>
    static void apply(Node *n, long long val, long long lx, long long rx) {
      n->value.sum = val * (rx - lx);
      n->value.av = val;
    }
    
    template<typename Node>
    static void push(Node *n, long long lx, long long rx) {
      if (n->value.av != __very_big_number) {
        long long m = (lx + rx) / 2;
        apply(n->left, n->value.av, lx, m);
        apply(n->right, n->value.av, m, rx);
        n->value.av = __very_big_number;
      }
    }
    
    Set__Sum operator+ (Set__Sum n) {
      Set__Sum ans;
      ans.sum = sum + n.sum;
      return ans;
    }
  };

  struct Add__Sum {
    long long sum, add;
    
    Add__Sum() : sum(0), add(0) {}
    
    Add__Sum(ll x) : sum(x), add(0) {}
    
    template<typename Node>
    static void apply(Node *n, long long val, long long lx, long long rx) {
      n->value.sum += val * (rx - lx);
      n->value.add += val;
    }
    
    template<typename Node>
    static void push(Node *n, long long lx, long long rx) {
      if (n->value.add != 0) {
        long long m = (lx + rx) / 2;
        apply(n->left, n->value.add, lx, m);
        apply(n->right, n->value.add, m, rx);
        n->value.add = 0;
      }
    }
    
    Add__Sum operator+ (Add__Sum n) {
      Add__Sum ans;
      ans.sum = sum + n.sum;
      return ans;
    }
  };
  
  struct Add__Min {
    long long mn, add;
    
    Add__Min() : mn(__very_big_number), add(0) {}
    
    Add__Min(ll x) : mn(x), add(0) {}
    
    template<typename Node>
    static void apply(Node *n, long long val, long long lx, long long rx) {
      n->value.mn += val;
      n->value.add += val;
    }
    
    template<typename Node>
    static void push(Node *n, long long lx, long long rx) {
      if (n->value.add != 0) {
        long long m = (lx + rx) / 2;
        apply(n->left, n->value.add, lx, m);
        apply(n->right, n->value.add, m, rx);
        n->value.add = 0;
      }
    }
    
    Add__Min operator+ (Add__Min n) {
      Add__Min ans;
      ans.mn = min(mn, n.mn);
      return ans;
    }
  };
  
  struct Add__Max {
    long long mx, add;
    
    Add__Max() : mx(-__very_big_number), add(0) {}
    
    Add__Max(ll x) : mx(x), add(0) {}
    
    template<typename Node>
    static void apply(Node *n, long long val, long long lx, long long rx) {
      n->value.mx += val;
      n->value.add += val;
    }
    
    template<typename Node>
    static void push(Node *n, long long lx, long long rx) {
      if (n->value.add != 0) {
        long long m = (lx + rx) / 2;
        apply(n->left, n->value.add, lx, m);
        apply(n->right, n->value.add, m, rx);
        n->value.add = 0;
      }
    }
    
    Add__Max operator+ (Add__Max n) {
      Add__Max ans;
      ans.mx = max(mx, n.mx);
      return ans;
    }
  };
}
