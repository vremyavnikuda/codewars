use std::collections::HashMap;

struct Solution;

impl Solution {
    pub fn count_trapezoids(points: Vec<Vec<i32>>) -> i32 {
        let n = points.len();
        let mut c1: HashMap<(i64, i64), HashMap<(i64, i64), i32>> = HashMap::new();
        let mut c2: HashMap<i32, HashMap<(i64, i64), i32>> = HashMap::new();

        fn gcd(a: i64, b: i64) -> i64 {
            if b == 0 { a.abs() } else { gcd(b, a % b) }
        }

        fn norm(dy: i64, dx: i64) -> (i64, i64) {
            if dx == 0 {
                return (1, 0);
            }
            let g = gcd(dy, dx);
            let (dy, dx) = (dy / g, dx / g);
            if dx < 0 { (-dy, -dx) } else { (dy, dx) }
        }

        for i in 0..n {
            let x1 = points[i][0] as i64;
            let y1 = points[i][1] as i64;

            for j in 0..i {
                let x2 = points[j][0] as i64;
                let y2 = points[j][1] as i64;

                let dx = x2 - x1;
                let dy = y2 - y1;
                let k = norm(dy, dx);

                let b = if dx == 0 {
                    (x1, 0)
                } else {
                    let num = y1 * dx - x1 * dy;
                    let g = gcd(num, dx);
                    let (num, den) = (num / g, dx / g);
                    if den < 0 { (-num, -den) } else { (num, den) }
                };

                *c1.entry(k).or_default().entry(b).or_insert(0) += 1;

                let p = ((x1 + x2 + 2000) * 4000 + (y1 + y2 + 2000)) as i32;
                *c2.entry(p).or_default().entry(k).or_insert(0) += 1;
            }
        }

        let mut a = 0i64;

        for e in c1.values() {
            let mut s = 0i64;
            for &t in e.values() {
                a += s * t as i64;
                s += t as i64;
            }
        }

        for e in c2.values() {
            let mut s = 0i64;
            for &t in e.values() {
                a -= s * t as i64;
                s += t as i64;
            }
        }

        a as i32
    }
}

fn main() {
    let r1 = Solution::count_trapezoids(vec![vec![0, 0], vec![1, 1], vec![2, 0], vec![3, 1]]);
    println!("{}", r1);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(
            Solution::count_trapezoids(vec![vec![0, 0], vec![1, 1], vec![2, 0], vec![3, 1],]),
            1
        );
    }

    #[test]
    fn t2() {
        assert_eq!(
            Solution::count_trapezoids(vec![vec![0, 0], vec![1, 0], vec![2, 0],]),
            0
        );
    }

    #[test]
    fn t3() {
        assert_eq!(
            Solution::count_trapezoids(vec![vec![0, 0], vec![2, 0], vec![1, 1], vec![3, 1],]),
            1
        );
    }
}
