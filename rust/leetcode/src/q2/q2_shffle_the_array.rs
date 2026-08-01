struct Solution;

impl Solution {
    pub fn shuffle(nums: Vec<i32>, n: i32) -> Vec<i32> {
        let n = n as usize;
        (0..n).flat_map(|i| [nums[i], nums[n + i]]).collect()
    }
}

fn main() {
    let r1 = Solution::shuffle(vec![2, 5, 1, 3, 4, 7], 3);
    let r2 = Solution::shuffle(vec![1, 2, 3, 4, 4, 3, 2, 1], 4);
    let r3 = Solution::shuffle(vec![1, 1, 2, 2], 2);

    println!("{:?}", r1);
    println!("{:?}", r2);
    println!("{:?}", r3);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(
            Solution::shuffle(vec![2, 5, 1, 3, 4, 7], 3),
            vec![2, 3, 5, 4, 1, 7]
        );
    }

    #[test]
    fn t2() {
        assert_eq!(
            Solution::shuffle(vec![1, 2, 3, 4, 4, 3, 2, 1], 4),
            vec![1, 4, 2, 3, 3, 2, 4, 1]
        );
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::shuffle(vec![1, 1, 2, 2], 2), vec![1, 2, 1, 2]);
    }
}
