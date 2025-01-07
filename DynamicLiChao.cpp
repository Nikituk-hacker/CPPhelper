const long double eps = 1e0;
const long long maxn = 1e10;
const long long inf = 1e18;

namespace Handmade {
  struct DynamicLiChaoTreeMin {
    struct Line {
      long double k, b;
      
      Line() : k(0), b(inf) {}
      
      Line(long double _k, long double _b) : k(_k), b(_b) {}
      
      long double operator() (long double x) const {
        return k * x + b;
      }
    };
    
    struct Node {
      Line val = {};
      Node *l = 0, *r = 0;
    };
    
    Node *root = 0;
    
    void insert_line(Line l) {
      insert_line(l, -maxn, maxn, root);
    }
    
    void insert_line(Line l, long double lx, long double rx, Node *&n) {
      if (!n) n = new Node();
      long double m = (lx + rx) / 2; 
      bool left = l(lx) < n->val(lx);
      bool mid = l(m) < n->val(m);
      if (mid) swap(l, n->val);
      if (rx - lx < eps) return;
      if (left != mid) {
        insert_line(l, lx, m, n->l);
      } else {
        insert_line(l, m, rx, n->r);
      }
    }
    
    long double get(long double x) {
      return get(x, -maxn, maxn, root);
    }
    
    long double get(long double x, long double lx, long double rx, Node *n) {
      if (!n) return inf;
      if (rx - lx < eps) return n->val(x);
      long double m = (lx + rx) / 2; 
      if (x < m) return min(n->val(x), get(x, lx, m, n->l));
      return min(n->val(x), get(x, m, rx, n->r));
    }
  };

  struct DynamicLiChaoTreeMax {
    struct Line {
      long double k, b;
      
      Line() : k(0), b(inf) {}
      
      Line(long double _k, long double _b) : k(_k), b(_b) {}
      
      long double operator() (long double x) const {
        return k * x + b;
      }
    };
    
    struct Node {
      Line val = {};
      Node *l = 0, *r = 0;
    };
    
    Node *root = 0;
    
    void insert_line(Line l) {
      insert_line(l, -maxn, maxn, root);
    }
    
    void insert_line(Line l, long double lx, long double rx, Node *&n) {
      if (!n) n = new Node();
      long double m = (lx + rx) / 2; 
      bool left = l(lx) > n->val(lx);
      bool mid = l(m) > n->val(m);
      if (mid) swap(l, n->val);
      if (rx - lx < eps) return;
      if (left != mid) {
        insert_line(l, lx, m, n->l);
      } else {
        insert_line(l, m, rx, n->r);
      }
    }
    
    long double get(long double x) {
      return get(x, -maxn, maxn, root);
    }
    
    long double get(long double x, long double lx, long double rx, Node *n) {
      if (!n) return inf;
      if (rx - lx < eps) return n->val(x);
      long double m = (lx + rx) / 2; 
      if (x < m) return max(n->val(x), get(x, lx, m, n->l));
      return max(n->val(x), get(x, m, rx, n->r));
    }
  };
}
