struct Solution;

impl Solution {
    pub fn max_subarray_sum(nums: Vec<i32>, k: i32) -> i64 {
        const I: i64 = 1_000_000_000_000_000_000;
        let k = k as usize;

        let mut m = vec![I; k];
        let mut r = -I;
        let mut p = 0i64;

        m[k - 1] = 0;

        for (i, &n) in nums.iter().enumerate() {
            p += n as i64;
            r = r.max(p - m[i % k]);
            m[i % k] = m[i % k].min(p);
        }

        r
    }
}

fn main() {
    let r1 = Solution::max_subarray_sum(vec![1, 2], 1);
    let r2 = Solution::max_subarray_sum(vec![-1, -2, -3, -4, -5], 4);
    let r3 = Solution::max_subarray_sum(vec![-5, 1, 2, -3, 4], 2);

    println!("{}", r1);
    println!("{}", r2);
    println!("{}", r3);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(Solution::max_subarray_sum(vec![1, 2], 1), 3);
    }

    #[test]
    fn t2() {
        assert_eq!(Solution::max_subarray_sum(vec![-1, -2, -3, -4, -5], 4), -10);
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::max_subarray_sum(vec![-5, 1, 2, -3, 4], 2), 4);
    }

    #[test]
    fn t4() {
        assert_eq!(Solution::max_subarray_sum(vec![1, -2, 3, -4, 5], 3), 4);
    }
}
