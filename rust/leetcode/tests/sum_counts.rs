struct Solution;

include!("../src/q1/q1_sum_counts.rs");

#[test]
fn aa() {
    assert_eq!(Solution::sum_counts(vec![1, 2, 1]), 15);
    assert_eq!(Solution::sum_counts(vec![1, 1]), 3);
    assert_eq!(Solution::sum_counts(vec![1, 2, 3]), 20);
    assert_eq!(Solution::sum_counts(vec![100]), 1);
    assert_eq!(Solution::sum_counts(vec![100; 100]), 5050);
    assert_eq!(Solution::sum_counts((1..=100).collect()), 8_670_850);
    assert_eq!(Solution::sum_counts(vec![]), 0);
}
