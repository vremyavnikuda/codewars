impl Solution {
    pub fn longest_subarray(nums: Vec<i32>, k: i32) -> i32 {
        fn asd(
            mut aa: usize,
            bb: bool,
            cc: &[u32; 100_001],
            dd: &mut [u32; 100_001],
            ee: &mut i32,
        ) {
            while aa > 1 {
                let ff = cc[aa] as usize;
                if bb {
                    if dd[ff] == 0 {
                        *ee += 1;
                    }
                    dd[ff] += 1;
                } else {
                    dd[ff] -= 1;
                    if dd[ff] == 0 {
                        *ee -= 1;
                    }
                }
                while aa % ff == 0 {
                    aa /= ff;
                }
            }
        }
        let aa = nums.iter().copied().max().unwrap_or(2) as usize;
        let mut bb = [0u32; 100_001];
        for cc in 2..=aa {
            if bb[cc] == 0 {
                bb[cc] = cc as u32;
                if cc <= aa / cc {
                    for dd in (cc * cc..=aa).step_by(cc) {
                        if bb[dd] == 0 {
                            bb[dd] = cc as u32;
                        }
                    }
                }
            }
        }
        let mut cc = [0u32; 100_001];
        let mut dd = 0;
        let mut ee = 0;
        let mut ff = 0;
        for (gg, &hh) in nums.iter().enumerate() {
            asd(hh as usize, true, &bb, &mut cc, &mut ee);

            while ee > k {
                asd(nums[dd] as usize, false, &bb, &mut cc, &mut ee);
                dd += 1;
            }
            ff = ff.max(gg + 1 - dd);
        }
        ff as i32
    }
}

#[cfg(test)]
mod aa {
    use super::*;

    #[test]
    fn bb() {
        assert_eq!(Solution::longest_subarray(vec![7, 6, 10, 12, 11], 3), 3);
        assert_eq!(Solution::longest_subarray(vec![4, 6, 9, 18], 4), 4);
        assert_eq!(Solution::longest_subarray(vec![6, 10, 15], 2), 1);
        assert_eq!(Solution::longest_subarray(vec![2, 4, 8, 16], 1), 4);
        assert_eq!(Solution::longest_subarray(vec![30], 2), 0);
    }
}
