use std::collections::{HashMap, HashSet, VecDeque};

struct Solution;

impl Solution {
    pub fn find_all_people(n: i32, meetings: Vec<Vec<i32>>, first_person: i32) -> Vec<i32> {
        let n = n as usize;
        let mut v = vec![false; n];
        v[0] = true;
        v[first_person as usize] = true;

        let mut m = meetings;
        m.sort_by_key(|x| x[2]);

        let mut i = 0;
        let len = m.len();

        while i < len {
            let mut j = i;
            while j + 1 < len && m[j + 1][2] == m[i][2] {
                j += 1;
            }

            let mut g: HashMap<i32, Vec<i32>> = HashMap::new();
            let mut s: HashSet<i32> = HashSet::new();

            for k in i..=j {
                let x = m[k][0];
                let y = m[k][1];
                g.entry(x).or_insert_with(Vec::new).push(y);
                g.entry(y).or_insert_with(Vec::new).push(x);
                s.insert(x);
                s.insert(y);
            }

            let mut q = VecDeque::new();
            for &u in &s {
                if v[u as usize] {
                    q.push_back(u);
                }
            }

            while let Some(u) = q.pop_front() {
                if let Some(neighbors) = g.get(&u) {
                    for &w in neighbors {
                        if !v[w as usize] {
                            v[w as usize] = true;
                            q.push_back(w);
                        }
                    }
                }
            }

            i = j + 1;
        }

        (0..n as i32).filter(|&i| v[i as usize]).collect()
    }
}

fn main() {
    let r1 = Solution::find_all_people(6, vec![vec![1, 2, 5], vec![2, 3, 8], vec![1, 5, 10]], 1);
    println!("{:?}", r1);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        let mut result =
            Solution::find_all_people(6, vec![vec![1, 2, 5], vec![2, 3, 8], vec![1, 5, 10]], 1);
        result.sort();
        assert_eq!(result, vec![0, 1, 2, 3, 5]);
    }

    #[test]
    fn t2() {
        let mut result =
            Solution::find_all_people(4, vec![vec![3, 1, 3], vec![1, 2, 2], vec![0, 3, 3]], 3);
        result.sort();
        assert_eq!(result, vec![0, 1, 3]);
    }

    #[test]
    fn t3() {
        let mut result =
            Solution::find_all_people(5, vec![vec![3, 4, 2], vec![1, 2, 1], vec![2, 3, 1]], 1);
        result.sort();
        assert_eq!(result, vec![0, 1, 2, 3, 4]);
    }
}
