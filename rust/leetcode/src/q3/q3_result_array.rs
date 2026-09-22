struct Solution;

impl Solution {
    pub fn result_array(nums: Vec<i32>, k: i32, queries: Vec<Vec<i32>>) -> Vec<i32> {
        type Nd = (i32, [i32; 5]);

        fn mg(aa: Nd, bb: Nd, cc: i32) -> Nd {
            let mut dd = aa;
            dd.0 = aa.0 * bb.0 % cc;
            for ee in 0..cc as usize {
                dd.1[(aa.0 * ee as i32 % cc) as usize] += bb.1[ee];
            }
            dd
        }

        fn lf(aa: i32, bb: i32) -> Nd {
            let cc = (aa % bb) as usize;
            let mut dd = (cc as i32, [0; 5]);
            dd.1[cc] = 1;
            dd
        }

        fn bd(aa: &mut [Nd], bb: usize, cc: usize, dd: usize, ee: &[i32], ff: i32) {
            if cc == dd {
                aa[bb] = lf(ee[cc], ff);
                return;
            }
            let gg = (cc + dd) / 2;
            bd(aa, bb << 1, cc, gg, ee, ff);
            bd(aa, bb << 1 | 1, gg + 1, dd, ee, ff);
            aa[bb] = mg(aa[bb << 1], aa[bb << 1 | 1], ff);
        }

        fn md(aa: &mut [Nd], bb: usize, cc: usize, dd: usize, ee: usize, ff: i32, gg: i32) {
            if cc == dd {
                aa[bb] = lf(ff, gg);
                return;
            }
            let hh = (cc + dd) / 2;
            if ee <= hh {
                md(aa, bb << 1, cc, hh, ee, ff, gg);
            } else {
                md(aa, bb << 1 | 1, hh + 1, dd, ee, ff, gg);
            }
            aa[bb] = mg(aa[bb << 1], aa[bb << 1 | 1], gg);
        }

        fn qr(aa: &[Nd], bb: usize, cc: usize, dd: usize, ee: usize, ff: usize, gg: i32) -> Nd {
            if cc >= ee && dd <= ff {
                return aa[bb];
            }
            let hh = (cc + dd) / 2;
            if ff <= hh {
                return qr(aa, bb << 1, cc, hh, ee, ff, gg);
            }
            if ee > hh {
                return qr(aa, bb << 1 | 1, hh + 1, dd, ee, ff, gg);
            }
            mg(
                qr(aa, bb << 1, cc, hh, ee, ff, gg),
                qr(aa, bb << 1 | 1, hh + 1, dd, ee, ff, gg),
                gg,
            )
        }

        let aa = nums.len();
        let mut bb: Vec<Nd> = vec![(1, [0; 5]); aa << 2];
        bd(&mut bb, 1, 0, aa - 1, &nums, k);
        queries
            .iter()
            .map(|cc| {
                md(&mut bb, 1, 0, aa - 1, cc[0] as usize, cc[1], k);
                qr(&bb, 1, 0, aa - 1, cc[2] as usize, aa - 1, k).1[cc[3] as usize]
            })
            .collect()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn bf(aa: &mut Vec<i32>, bb: i32, cc: &[Vec<i32>]) -> Vec<i32> {
        cc.iter()
            .map(|dd| {
                aa[dd[0] as usize] = dd[1];
                let mut ee = 1;
                (dd[2] as usize..aa.len())
                    .filter(|ff| {
                        ee = ee * (aa[*ff] % bb) % bb;
                        ee == dd[3]
                    })
                    .count() as i32
            })
            .collect()
    }

    #[test]
    fn t1() {
        assert_eq!(
            Solution::result_array(
                vec![1, 2, 3, 4, 5],
                3,
                vec![vec![0, 2, 0, 2], vec![3, 3, 3, 0], vec![0, 1, 0, 1]]
            ),
            bf(
                &mut vec![1, 2, 3, 4, 5],
                3,
                &[vec![0, 2, 0, 2], vec![3, 3, 3, 0], vec![0, 1, 0, 1]]
            )
        );
    }

    #[test]
    fn t2() {
        // pseudo-random cross-check against brute force
        let mut aa: Vec<i32> = (0..40).map(|bb| (bb * 37 % 11) + 1).collect();
        let cc: Vec<Vec<i32>> = (0..40i32)
            .map(|dd| {
                vec![
                    dd % 40,
                    (dd * 13 % 9) + 1,
                    dd * 7 % 40,
                    dd % 5,
                ]
            })
            .collect();
        assert_eq!(
            Solution::result_array(aa.clone(), 5, cc.clone()),
            bf(&mut aa, 5, &cc)
        );
    }
}
