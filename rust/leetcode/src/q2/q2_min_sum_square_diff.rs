impl Solution {
    pub fn min_sum_square_diff(nums1: Vec<i32>, nums2: Vec<i32>, k1: i32, k2: i32) -> i64 {
        let mut aa = i64::from(k1) + i64::from(k2);
        let mut bb = 0i64;
        let mut cc = [0i32; 100_001];
        let mut dd = 0usize;
        for (&ee, &ff) in nums1.iter().zip(&nums2) {
            let gg = (ee - ff).unsigned_abs() as usize;
            cc[gg] += 1;
            bb += gg as i64;
            dd = dd.max(gg);
        }
        if bb <= aa {
            return 0;
        }
        for ee in (1..=dd).rev() {
            if aa == 0 {
                break;
            }
            if cc[ee] == 0 {
                continue;
            }
            let ff = i64::from(cc[ee]).min(aa) as i32;
            aa -= i64::from(ff);
            cc[ee] -= ff;
            cc[ee - 1] += ff;
        }
        cc[..=dd]
            .iter()
            .enumerate()
            .map(|(ee, &ff)| {
                let gg = ee as i64;
                gg * gg * i64::from(ff)
            })
            .sum()
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;
    #[test]
    fn t1() {
        assert_eq!(
            Solution::min_sum_square_diff(vec![1, 2, 3, 4], vec![2, 10, 20, 19], 0, 0),
            579
        );
        assert_eq!(
            Solution::min_sum_square_diff(vec![1, 4, 10, 12], vec![5, 8, 6, 9], 1, 1),
            43
        );
        assert_eq!(
            Solution::min_sum_square_diff(vec![5, 5, 5], vec![0, 0, 0], 1, 1),
            57
        );
        assert_eq!(
            Solution::min_sum_square_diff(vec![5, 1], vec![0, 0], 3, 0),
            5
        );
        assert_eq!(
            Solution::min_sum_square_diff(vec![1, 2], vec![2, 1], 1, 1),
            0
        );
        assert_eq!(Solution::min_sum_square_diff(vec![1], vec![1], 10, 10), 0);
        assert_eq!(
            Solution::min_sum_square_diff(vec![100_000], vec![0], 0, 0),
            10_000_000_000
        );
        assert_eq!(
            Solution::min_sum_square_diff(
                vec![100_000; 100_000],
                vec![0; 100_000],
                1_000_000_000,
                1_000_000_000
            ),
            640_000_000_000_000
        );
    }
}
