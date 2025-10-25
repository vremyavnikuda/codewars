use std::collections::HashMap;

pub struct Solution;

impl Solution {
    pub fn sum_of_ancestors(n: i32, edges: Vec<Vec<i32>>, nums: Vec<i32>) -> i64 {
        let n = n as usize;
        
        let mut graph = vec![Vec::new(); n];
        for edge in edges {
            let u = edge[0] as usize;
            let v = edge[1] as usize;
            graph[u].push(v);
            graph[v].push(u);
        }
        
        let signatures: Vec<i32> = nums.iter().map(|&x| Self::get_signature(x)).collect();
        
        let mut total = 0i64;
        
        let mut stack = vec![(0, None, 0, HashMap::new())];
        
        while let Some((node, parent, phase, mut sig_counts)) = stack.pop() {
            if phase == 0 {
                if node != 0 {
                    let current_sig = signatures[node];
                    let count = sig_counts.get(&current_sig).unwrap_or(&0);
                    total += *count as i64;
                }
                
                *sig_counts.entry(signatures[node]).or_insert(0) += 1;
                
                for &child in &graph[node] {
                    if Some(child) != parent {
                        stack.push((child, Some(node), 0, sig_counts.clone()));
                    }
                }
            }
        }
        
        total
    }
    
    pub fn get_signature(mut num: i32) -> i32 {
        let mut signature = 1;
        let mut d = 2;
        
        while d * d <= num {
            let mut count = 0;
            while num % d == 0 {
                num /= d;
                count += 1;
            }
            if count % 2 == 1 {
                signature *= d;
            }
            d += 1;
        }
        
        if num > 1 {
            signature *= num;
        }
        
        signature
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example_1() {
        let n = 3;
        let edges = vec![vec![0, 1], vec![1, 2]];
        let nums = vec![2, 8, 2];
        assert_eq!(Solution::sum_of_ancestors(n, edges, nums), 3);
    }

    #[test]
    fn test_example_2() {
        let n = 3;
        let edges = vec![vec![0, 1], vec![0, 2]];
        let nums = vec![1, 2, 4];
        assert_eq!(Solution::sum_of_ancestors(n, edges, nums), 1);
    }

    #[test]
    fn test_example_3() {
        let n = 4;
        let edges = vec![vec![0, 1], vec![0, 2], vec![1, 3]];
        let nums = vec![1, 2, 9, 4];
        assert_eq!(Solution::sum_of_ancestors(n, edges, nums), 2);
    }

    #[test]
    fn test_signature() {
        assert_eq!(Solution::get_signature(2), 2);
        assert_eq!(Solution::get_signature(8), 2);
        assert_eq!(Solution::get_signature(4), 1);
        assert_eq!(Solution::get_signature(9), 1);
        assert_eq!(Solution::get_signature(1), 1);
    }

    #[test]
    fn test_single_node() {
        let n = 1;
        let edges = vec![];
        let nums = vec![1];
        assert_eq!(Solution::sum_of_ancestors(n, edges, nums), 0);
    }

    #[test]
    fn test_all_perfect_squares() {
        let n = 3;
        let edges = vec![vec![0, 1], vec![1, 2]];
        let nums = vec![1, 1, 1];
        assert_eq!(Solution::sum_of_ancestors(n, edges, nums), 3);
    }

    #[test]
    fn test_no_matches() {
        let n = 3;
        let edges = vec![vec![0, 1], vec![1, 2]];
        let nums = vec![2, 3, 5];
        assert_eq!(Solution::sum_of_ancestors(n, edges, nums), 0);
    }
}
