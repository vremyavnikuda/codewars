impl Solution {
    pub fn min_swaps(nums: Vec<i32>) -> i32 {
        let mut aa: Vec<_> = nums
            .iter()
            .enumerate()
            .map(|(bb, &cc)| {
                let mut dd = cc;
                let mut ee = 0;
                while dd != 0 {
                    ee += dd % 10;
                    dd /= 10;
                }
                (ee, cc, bb)
            })
            .collect();
        aa.sort_unstable();
        let mut bb = 0;
        for cc in 0..aa.len() {
            while aa[cc].2 != cc {
                let dd = aa[cc].2;
                aa.swap(cc, dd);
                bb += 1;
            }
        }
        bb
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn digit_order_and_cycles() {
        assert_eq!(Solution::min_swaps(vec![]), 0);
        assert_eq!(Solution::min_swaps(vec![7]), 0);
        assert_eq!(Solution::min_swaps(vec![37, 100]), 1);
        assert_eq!(Solution::min_swaps(vec![22, 14, 33, 7]), 0);
        assert_eq!(Solution::min_swaps(vec![18, 43, 34, 16]), 2);
        assert_eq!(Solution::min_swaps(vec![3, 1, 2]), 2);
        assert_eq!(Solution::min_swaps(vec![21, 12, 30]), 1);
    }
}
