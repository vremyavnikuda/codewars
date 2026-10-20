impl Solution {
    pub fn sortable_integers(nums: Vec<i32>) -> i32 {
        let aa = nums.len();
        let bb = |cc: usize| {
            let mut dd = i32::MIN;
            for ee in nums.chunks_exact(cc) {
                let mut ff = ee[cc - 1];
                let mut gg = 0;
                let mut hh = dd;
                for &ii in ee {
                    gg += usize::from(ff > ii);
                    if gg > 1 || dd > ii {
                        return false;
                    }
                    hh = hh.max(ii);
                    ff = ii;
                }
                dd = hh;
            }
            true
        };
        let mut jj = 0;
        let mut kk = 1;
        while kk <= aa / kk {
            if aa % kk == 0 {
                if bb(kk) {
                    jj += kk as i32;
                }
                let ll = aa / kk;
                if kk != ll && bb(ll) {
                    jj += ll as i32;
                }
            }
            kk += 1;
        }
        jj
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;
    #[test]
    fn sortable_integers_examples() {
        for (aa, bb) in [
            (vec![], 0),
            (vec![1], 1),
            (vec![1, 2, 3, 4], 7),
            (vec![2, 1, 4, 3], 2),
            (vec![3, 4, 1, 2], 4),
            (vec![4, 3, 2, 1], 0),
            (vec![2, 2, 2, 2], 7),
            (vec![i32::MAX, i32::MIN], 2),
        ] {
            assert_eq!(Solution::sortable_integers(aa), bb);
        }
    }
}
