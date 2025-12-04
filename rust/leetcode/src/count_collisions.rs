struct Solution;

impl Solution {
    pub fn count_collisions(directions: String) -> i32 {
        let s: Vec<char> = directions.chars().collect();
        let n = s.len();

        let mut l = 0;
        while l < n && s[l] == 'L' {
            l += 1;
        }

        let mut r = n as i32 - 1;
        while r >= 0 && s[r as usize] == 'R' {
            r -= 1;
        }

        if l as i32 > r {
            return 0;
        }

        let t = (r - l as i32 + 1) as usize;
        let c = s[l..=r as usize].iter().filter(|&&x| x == 'S').count();

        (t - c) as i32
    }
}

fn main() {
    let r1 = Solution::count_collisions("RLRSLL".to_string());
    let r2 = Solution::count_collisions("LLRR".to_string());

    println!("{}", r1);
    println!("{}", r2);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(Solution::count_collisions("RLRSLL".to_string()), 5);
    }

    #[test]
    fn t2() {
        assert_eq!(Solution::count_collisions("LLRR".to_string()), 0);
    }

    #[test]
    fn t3() {
        assert_eq!(
            Solution::count_collisions("SSRSSRLLRSLLRSRSSRLRRRRLLRRLSSRR".to_string()),
            20
        );
    }

    #[test]
    fn t4() {
        assert_eq!(Solution::count_collisions("S".to_string()), 0);
    }
}
