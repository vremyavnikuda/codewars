// No solution for this problem was available in the provided context.
impl Solution {
    pub fn valid_subarrays(nums: Vec<i32>, k: i32, queries: Vec<Vec<i32>>) -> Vec<bool> {
        fn qwe(
            aa: usize,
            bb: bool,
            cc: &[i32],
            dd: &mut [u32; 100_001],
            ee: &mut i32,
            ff: &mut i32,
        ) {
            let gg = cc[aa] as usize;
            if dd[gg] & 1 == 0 {
                *ff += 1;
            } else {
                *ff -= 1;
            }
            if bb {
                if dd[gg] == 0 {
                    *ee += 1;
                }
                dd[gg] += 1;
            } else {
                dd[gg] -= 1;
                if dd[gg] == 0 {
                    *ee -= 1;
                }
            }
        }
        let mut aa = queries
            .iter()
            .enumerate()
            .map(|(bb, cc)| (cc[0] as usize, cc[1] as usize, bb))
            .collect::<Vec<_>>();
        let bb = (nums.len() as f64).sqrt() as usize + 1;
        aa.sort_unstable_by_key(|cc| {
            let dd = cc.0 / bb;
            (dd, if dd & 1 == 0 { cc.1 } else { usize::MAX - cc.1 })
        });
        let mut cc = vec![false; aa.len()];
        let mut dd = [0u32; 100_001];
        let mut ee = 0;
        let mut ff = 0;
        let mut gg = 0;
        let mut hh = 0;
        for &(ii, jj, ll) in &aa {
            while gg > ii {
                gg -= 1;
                qwe(gg, true, &nums, &mut dd, &mut ee, &mut ff);
            }
            while hh <= jj {
                qwe(hh, true, &nums, &mut dd, &mut ee, &mut ff);
                hh += 1;
            }
            while gg < ii {
                qwe(gg, false, &nums, &mut dd, &mut ee, &mut ff);
                gg += 1;
            }
            while hh > jj + 1 {
                hh -= 1;
                qwe(hh, false, &nums, &mut dd, &mut ee, &mut ff);
            }
            cc[ll] = ee == k && ff == 0;
        }
        cc
    }
}

#[cfg(test)]
mod aa {
    use super::*;

    #[test]
    fn bb() {
        assert_eq!(
            Solution::valid_subarrays(
                vec![1, 2, 2, 1],
                2,
                vec![vec![0, 1], vec![0, 3], vec![1, 2]],
            ),
            vec![false, true, false]
        );
        assert_eq!(
            Solution::valid_subarrays(vec![3, 3, 3], 1, vec![vec![1, 2], vec![0, 2]]),
            vec![true, false]
        );
        assert_eq!(
            Solution::valid_subarrays(
                vec![1, 1, 2, 2, 3, 3],
                2,
                vec![vec![2, 5], vec![0, 5], vec![1, 4], vec![0, 3]],
            ),
            vec![true, false, false, true]
        );
        assert_eq!(
            Solution::valid_subarrays(
                vec![100_000, 100_000, 100_000, 100_000],
                1,
                vec![vec![1, 2], vec![0, 2], vec![0, 3]],
            ),
            vec![true, false, true]
        );
    }

    #[test]
    fn cc() {
        let aa = (0usize..100_000)
            .map(|bb| {
                let cc = bb.wrapping_mul(7_919) % 99_999;
                let dd = cc + 1 + bb.wrapping_mul(31_337) % (99_999 - cc);
                vec![cc as i32, dd as i32]
            })
            .collect::<Vec<_>>();
        let bb = aa
            .iter()
            .map(|cc| (cc[1] - cc[0]) & 1 == 1)
            .collect::<Vec<_>>();

        assert_eq!(Solution::valid_subarrays(vec![1; 100_000], 1, aa), bb);
    }

    #[test]
    fn dd() {
        let aa = (0usize..100_000)
            .map(|bb| vec![bb as i32 % 99_999, bb as i32 % 99_999 + 1])
            .collect::<Vec<_>>();

        assert_eq!(
            Solution::valid_subarrays((1..=100_000).collect(), 1, aa),
            vec![false; 100_000]
        );
    }
}
