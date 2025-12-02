use std::collections::HashMap;

struct Solution;

impl Solution {
    pub fn count_trapezoids(points: Vec<Vec<i32>>) -> i32 {
        const M: i64 = 1_000_000_007;

        let mut c: HashMap<i32, i64> = HashMap::new();
        for p in &points {
            *c.entry(p[1]).or_insert(0) += 1;
        }

        let mut a = 0i64;
        let mut s = 0i64;

        for &v in c.values() {
            let t = v * (v - 1) / 2;
            a = (a + s * t) % M;
            s += t;
        }

        a as i32
    }
}

fn main() {
    let r1 = Solution::count_trapezoids(vec![
        vec![0, 0],
        vec![1, 0],
        vec![2, 0],
        vec![3, 0],
        vec![0, 1],
        vec![1, 1],
        vec![2, 1],
        vec![3, 1],
    ]);

    println!("{}", r1);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(
            Solution::count_trapezoids(vec![
                vec![0, 0],
                vec![1, 0],
                vec![2, 0],
                vec![3, 0],
                vec![0, 1],
                vec![1, 1],
                vec![2, 1],
                vec![3, 1],
            ]),
            36
        );
    }

    #[test]
    fn t2() {
        assert_eq!(
            Solution::count_trapezoids(vec![vec![0, 0], vec![1, 1], vec![2, 2],]),
            0
        );
    }

    #[test]
    fn t3() {
        assert_eq!(
            Solution::count_trapezoids(vec![vec![0, 0], vec![1, 0], vec![0, 1], vec![1, 1],]),
            1
        );
    }
}
