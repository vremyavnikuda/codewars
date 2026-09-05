#!/usr/bin/env rust-script

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

pub struct Solution;

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

// Main функция для независимого запуска
// Запуск: rustc src/process_queries.rs && ./process_queries (Linux/Mac)
// или    : rustc src\process_queries.rs -o process_queries.exe && .\process_queries.exe (Windows)

fn main() {
    // Тестовый пример 1
    let c = 5;
    let connections = vec![vec![1, 2], vec![3, 4]];
    let queries = vec![vec![1, 1], vec![2, 1], vec![1, 1]];

    let result = Solution::process_queries(c, connections.clone(), queries.clone());
    println!("Test 1:");
    println!("  c = {}", c);
    println!("  connections = {:?}", connections);
    println!("  queries = {:?}", queries);
    println!("  result = {:?}", result);
    println!();

    // Тестовый пример 2
    let c2 = 3;
    let connections2 = vec![vec![1, 2]];
    let queries2 = vec![vec![1, 3], vec![1, 1], vec![2, 2], vec![1, 2]];

    let result2 = Solution::process_queries(c2, connections2.clone(), queries2.clone());
    println!("Test 2:");
    println!("  c = {}", c2);
    println!("  connections = {:?}", connections2);
    println!("  queries = {:?}", queries2);
    println!("  result = {:?}", result2);

    println!("\n✅ All tests completed!");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example_1() {
        let c = 5;
        let connections = vec![vec![1, 2], vec![3, 4]];
        let queries = vec![vec![1, 1], vec![2, 1], vec![1, 1]];
        let result = Solution::process_queries(c, connections, queries);
        println!("Test result: {:?}", result);
    }
}
