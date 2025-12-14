struct Solution;

impl Solution {
    pub fn number_of_ways(corridor: String) -> i32 {
        let s: Vec<char> = corridor.chars().collect();
        let n = s.len();
        let m = 1_000_000_007i64;

        let mut d = vec![vec![-1i64; 3]; n + 1];

        fn f(i: usize, c: usize, s: &[char], d: &mut Vec<Vec<i64>>, m: i64) -> i64 {
            if i >= s.len() {
                return if c == 2 { 1 } else { 0 };
            }

            if d[i][c] != -1 {
                return d[i][c];
            }

            let nc = if s[i] == 'S' { c + 1 } else { c };

            if nc > 2 {
                d[i][c] = 0;
                return 0;
            }

            let mut r = f(i + 1, nc, s, d, m);

            if nc == 2 {
                r = (r + f(i + 1, 0, s, d, m)) % m;
            }

            d[i][c] = r;
            r
        }

        f(0, 0, &s, &mut d, m) as i32
    }
}

fn main() {
    let r1 = Solution::number_of_ways("SSPPSPS".to_string());
    let r2 = Solution::number_of_ways("PPSPSP".to_string());
    let r3 = Solution::number_of_ways("S".to_string());

    println!("{}", r1);
    println!("{}", r2);
    println!("{}", r3);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(Solution::number_of_ways("SSPPSPS".to_string()), 3);
    }

    #[test]
    fn t2() {
        assert_eq!(Solution::number_of_ways("PPSPSP".to_string()), 1);
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::number_of_ways("S".to_string()), 0);
    }

    #[test]
    fn t4() {
        assert_eq!(Solution::number_of_ways("PPPPPSPPSPPSPPPSPPPPSPPPPSPPPPSPPSPPPSPSPPPSPSPPPSPSPPPSPSPPPPSPPPPSPPPSPPSPPPPSPSPPPPSPSPPPPSPSPPPSPPSPPPPSPSPSS".to_string()), 919999993);
    }
}
