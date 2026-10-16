struct Solution;

include!("../src/q3/q3_sum_counts.rs");

#[test]
fn examples_and_boundaries() {
    assert_eq!(Solution::sum_counts(vec![]), 0);
    assert_eq!(Solution::sum_counts(vec![100]), 1);
    assert_eq!(Solution::sum_counts(vec![1, 2, 1]), 15);
    assert_eq!(Solution::sum_counts(vec![1, 1]), 3);
    assert_eq!(Solution::sum_counts(vec![1, 2, 3]), 20);
    assert_eq!(Solution::sum_counts(vec![i32::MIN, i32::MAX, i32::MIN]), 15);
}

#[test]
fn matches_direct_count() {
    for aa in 0..=7 {
        for mut bb in 0..3_usize.pow(aa) {
            let cc: Vec<i32> = (0..aa)
                .map(|_| {
                    let dd = (bb % 3) as i32;
                    bb /= 3;
                    dd
                })
                .collect();
            let mut dd = 0;
            for ee in 0..cc.len() {
                let mut ff = std::collections::HashSet::new();
                for &gg in &cc[ee..] {
                    ff.insert(gg);
                    dd += (ff.len() * ff.len()) as i32;
                }
            }
            assert_eq!(Solution::sum_counts(cc.clone()), dd, "{cc:?}");
        }
    }
}

#[test]
fn large_inputs_and_modulo() {
    let aa = 100_000_u128;
    assert_eq!(
        Solution::sum_counts(vec![1; aa as usize]),
        (aa * (aa + 1) / 2 % 1_000_000_007) as i32
    );
    assert_eq!(
        Solution::sum_counts((1..=aa as i32).collect()),
        (aa * (aa + 1) * (aa + 1) * (aa + 2) / 12 % 1_000_000_007) as i32
    );
}
