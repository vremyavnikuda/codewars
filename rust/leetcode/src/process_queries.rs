struct UnionFind {
    p: Vec<usize>,
    size: Vec<usize>,
}

impl UnionFind {
    fn new(n: usize) -> Self {
        let mut p = vec![0; n];
        for i in 0..n {
            p[i] = i;
        }
        Self {
            p,
            size: vec![1; n],
        }
    }

    fn find(&mut self, x: usize) -> usize {
        if self.p[x] != x {
            self.p[x] = self.find(self.p[x]);
        }
        self.p[x]
    }

    fn unite(&mut self, a: usize, b: usize) -> bool {
        let pa = self.find(a);
        let pb = self.find(b);
        if pa == pb {
            return false;
        }
        if self.size[pa] > self.size[pb] {
            self.p[pb] = pa;
            self.size[pa] += self.size[pb];
        } else {
            self.p[pa] = pb;
            self.size[pb] += self.size[pa];
        }
        true
    }
}

impl Solution {
    pub fn process_queries(c: i32, connections: Vec<Vec<i32>>, queries: Vec<Vec<i32>>) -> Vec<i32> {
        let mut uf = UnionFind::new((c + 1) as usize);
        
        // Process connections
        for connection in connections {
            uf.unite(connection[0] as usize, connection[1] as usize);
        }

        // Create sets for each component
        use std::collections::BTreeSet;
        let mut st: Vec<BTreeSet<usize>> = vec![BTreeSet::new(); (c + 1) as usize];
        for i in 1..=c as usize {
            let root = uf.find(i);
            st[root].insert(i);
        }

        let mut ans = Vec::new();
        for query in queries {
            let a = query[0];
            let x = query[1] as usize;
            let root = uf.find(x);
            
            if a == 1 {
                if st[root].contains(&x) {
                    ans.push(x as i32);
                } else if !st[root].is_empty() {
                    ans.push(*st[root].iter().next().unwrap() as i32);
                } else {
                    ans.push(-1);
                }
            } else {
                st[root].remove(&x);
            }
        }
        
        ans
    }
}