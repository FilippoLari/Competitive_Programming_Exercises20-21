#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <bits/stdc++.h>

using namespace std;

#define LEFT(i)     2 * i + 1
#define RIGHT(i)    2 * i + 2
#define PARENT(i) (i - 1) / 2

template<typename IntType, typename BinaryFunct>
struct rmq_segment_tree {

    struct type_traits {
        IntType invalid;
        BinaryFunct funct;
    };

    struct builder {

        builder()
        {}

        builder(std::vector<IntType> const& leaves, type_traits traits)
            : m_traits(traits)
        {
            size_t n = leaves.size();
            // round up to the next power of 2
            size_t m = size_t(1) << static_cast<size_t>(ceil(log2(n)));
            m_tree.resize(2 * m - 1, m_traits.invalid);
            build(leaves, 0, n - 1, 0);

            // for (auto x: m_tree) {
            //     std::cout << x << " ";
            // }   std::cout << std::endl;
        }

        void swap(builder& other) {
            std::swap(other.m_traits, m_traits);
            other.m_tree.swap(m_tree);
        }

        void build(rmq_segment_tree& rst) {
            std::swap(rst.m_traits, m_traits);
            rst.m_tree.swap(m_tree);
            builder().swap(*this);
        }

    private:
        type_traits m_traits;
        std::vector<IntType> m_tree;

        void build(std::vector<IntType> const& leaves, size_t lo, size_t hi, size_t pos) {
            if (lo == hi) {
                m_tree[pos] = leaves[lo];
                return;
            }
            size_t mid = (lo + hi) / 2;
            build(leaves, lo, mid, LEFT(pos));
            build(leaves, mid + 1, hi, RIGHT(pos));
            m_tree[pos] = m_traits.funct(m_tree[LEFT(pos)], m_tree[RIGHT(pos)]);
        }
    };

    rmq_segment_tree()
    {}

    // debug purposes
    void print_tree() const {
        for (auto x: m_tree) {
            std::cout << x << " ";
        }   std::cout << std::endl;
    }

    struct range {
        range(size_t l, size_t h)
            : lo(l), hi(h)
        {}

        size_t lo, hi;
    };

    range root() const {
        return range(0, size() - 1);
    }

    size_t size() const {
        return m_tree.size() / 2 + 1;
    }

    IntType rmq(range const& query, range node_segment, size_t pos) {

        if (query.lo <= node_segment.lo
        and query.hi >= node_segment.hi) { // total overlap
            return m_tree[pos];
        }
        if (query.lo > node_segment.hi
        or  query.hi < node_segment.lo) { // no overlap
            return m_traits.invalid;
        }

        // partial overlap
        size_t mid = (node_segment.lo + node_segment.hi) / 2;
        return m_traits.funct(
            rmq(query, {node_segment.lo, mid}, LEFT(pos)),
            rmq(query, {mid + 1, node_segment.hi}, RIGHT(pos))
        );
    }

    // increment the i-th leaf by delta
    void update(size_t i, IntType delta, range node_segment, size_t pos) {

        if (i > node_segment.hi
        or  i < node_segment.lo) {
            return;
        }

        if (node_segment.lo == node_segment.hi) { // leaf
            m_tree[pos] += delta;
            return;
        }

        size_t mid = (node_segment.lo + node_segment.hi) / 2;
        update(i, delta, {node_segment.lo, mid}, LEFT(pos));
        update(i, delta, {mid + 1, node_segment.hi}, RIGHT(pos));
        m_tree[pos] = m_traits.funct(m_tree[LEFT(pos)], m_tree[RIGHT(pos)]);
    }

    // increment all leaves in the range [query.lo, query.hi] by delta
    void update_range(range const& query, IntType delta, range node_segment, size_t pos) {

        if (query.lo > node_segment.hi
        or  query.hi < node_segment.lo) {
            return;
        }

        if (node_segment.lo == node_segment.hi) { // leaf
            m_tree[pos] += delta;
            return;
        }

        size_t mid = (node_segment.lo + node_segment.hi) / 2;
        update_range(query, delta, {node_segment.lo, mid}, LEFT(pos));
        update_range(query, delta, {mid + 1, node_segment.hi}, RIGHT(pos));
        m_tree[pos] = m_traits.funct(m_tree[LEFT(pos)], m_tree[RIGHT(pos)]);
    }

private:
    type_traits m_traits;
    std::vector<IntType> m_tree;
};

template<typename IntType>
struct range_min_query_operator {
    IntType operator()(IntType x, IntType y) {
        return std::min<IntType>(x, y);
    }
};


/*
    The algorithm uses a segment tree where range updates
    are handled with the lazy propagation method.

    In order to solve circular queries i.e when l > r, it
    splits them in two queries (l,n-1) and (0,r), then
    takes the minimum of the two results.

    Note: the solution uses this segment tree implementation
          https://github.com/rossanoventurini/CompetitiveProgramming/tree/master/code/segment_trees
          unfortunately, it is not accepted by the site because of a signed overflow at line 140
          which i think doesn't depend on my portion of code and i was not able to solve.

    Time: each query can be a range update or at most two range minimum queries, overall
          they take O(q logn) to be executed.

    Space: O(n) because of the segment tree.
*/


int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int64_t n, m, i;
    size_t l, r;
    char *v;

    cin >> n;

    vector<int64_t> leaves(n);

    for (i = 0; i < n; i++)
        cin >> leaves[i];

    typedef rmq_segment_tree<int64_t, range_min_query_operator<int64_t>> segment_tree_type;

    segment_tree_type::type_traits traits;
    traits.invalid = std::numeric_limits<int64_t>::max();

    segment_tree_type::builder builder(leaves, traits);
    segment_tree_type min_seg_tree;
    builder.build(min_seg_tree);

    cin >> m;

    char line[32];
	cin.getline(line, 32);

    for(i=0; i<m; i++)
    {
        cin.getline(line, 32);
		l = atoi(strtok(line, " "));
		r = atoi(strtok(NULL, " "));
		v = strtok(NULL, " ");

        if(l>r)
        {
            segment_tree_type::range qr1(l, n-1);
            segment_tree_type::range qr2(0,r);

            if(v==NULL)
            {
                int64_t min1 = min_seg_tree.rmq(qr1,min_seg_tree.root(),0);
                int64_t min2 = min_seg_tree.rmq(qr2,min_seg_tree.root(),0);

                cout << ((min1<min2)?min1:min2 ) << "\n"; 
            }
            else
            {
                min_seg_tree.update_range(qr1, atoi(v), min_seg_tree.root(), 0);
                min_seg_tree.update_range(qr2, atoi(v), min_seg_tree.root(), 0);
            }
        }
        else
        {
            segment_tree_type::range qr(l,r);
            if(v==NULL) cout << min_seg_tree.rmq(qr,min_seg_tree.root(),0) << "\n";
            else min_seg_tree.update_range(qr, atoi(v), min_seg_tree.root(), 0);
        }
    }

    return 0;
}