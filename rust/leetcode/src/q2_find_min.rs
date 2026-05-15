pub struct Solution;

impl Solution {
    #[inline(always)]
    pub fn find_min(nums: Vec<i32>) -> i32 {
        let (mut a, mut b, p) = (0usize, nums.len(), nums.as_ptr());
        unsafe {
            let z = *p.add(b - 1);
            while a < b {
                let c = a + ((b - a) >> 1);
                match (*p.add(c) <= z) as u8 {
                    0 => a = c + 1,
                    _ => b = c,
                }
            }
            *p.add(a)
        }
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;

    #[test]
    fn t1() {
        assert_eq!(Solution::find_min(vec![3, 4, 5, 1, 2]), 1);
    }

    #[test]
    fn t2() {
        assert_eq!(Solution::find_min(vec![4, 5, 6, 7, 0, 1, 2]), 0);
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::find_min(vec![11, 13, 15, 17]), 11);
    }
}
