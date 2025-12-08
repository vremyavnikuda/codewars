struct Solution;

impl Solution {
    pub fn count_triples(n: i32) -> i32 {
        let mut r = 0;

        for a in 1..n {
            for b in 1..n {
                let s = a * a + b * b;
                let c = (s as f64).sqrt() as i32;

                if c <= n && c * c == s {
                    r += 1;
                }
            }
        }

        r
    }
}

fn main() {
    let r1 = Solution::count_triples(5);
    let r2 = Solution::count_triples(10);

    println!("{}", r1);
    println!("{}", r2);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(Solution::count_triples(5), 2);
    }

    #[test]
    fn t2() {
        assert_eq!(Solution::count_triples(10), 4);
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::count_triples(15), 6);
    }

    #[test]
    fn t4() {
        assert_eq!(Solution::count_triples(1), 0);
    }
}
