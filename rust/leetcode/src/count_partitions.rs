struct Solution;

impl Solution {
    pub fn count_partitions(nums: Vec<i32>) -> i32 {
        let mut l = 0;
        let mut r: i32 = nums.iter().sum();
        let mut c = 0;

        for i in 0..nums.len() - 1 {
            l += nums[i];
            r -= nums[i];

            if (l - r) % 2 == 0 {
                c += 1;
            }
        }

        c
    }
}

fn main() {
    let r1 = Solution::count_partitions(vec![1, 2, 3, 4]);
    let r2 = Solution::count_partitions(vec![1, 2, 2]);

    println!("{}", r1);
    println!("{}", r2);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(Solution::count_partitions(vec![1, 2, 3, 4]), 2);
    }

    #[test]
    fn t2() {
        assert_eq!(Solution::count_partitions(vec![1, 2, 2]), 1);
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::count_partitions(vec![2, 4, 6, 8]), 3);
    }

    #[test]
    fn t4() {
        assert_eq!(Solution::count_partitions(vec![1, 1]), 1);
    }
}
