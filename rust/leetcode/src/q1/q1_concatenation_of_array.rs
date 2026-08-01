struct Solution;

impl Solution {
    pub fn get_concatenation(nums: Vec<i32>) -> Vec<i32> {
        [&nums[..], &nums[..]].concat()
    }
}

fn main() {
    let r1 = Solution::get_concatenation(vec![1, 2, 1]);
    let r2 = Solution::get_concatenation(vec![1, 3, 2, 1]);

    println!("{:?}", r1);
    println!("{:?}", r2);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(
            Solution::get_concatenation(vec![1, 2, 1]),
            vec![1, 2, 1, 1, 2, 1]
        );
    }

    #[test]
    fn t2() {
        assert_eq!(
            Solution::get_concatenation(vec![1, 3, 2, 1]),
            vec![1, 3, 2, 1, 1, 3, 2, 1]
        );
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::get_concatenation(vec![5]), vec![5, 5]);
    }
}
