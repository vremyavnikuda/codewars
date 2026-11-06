struct Solution;

include!("../src/q2/q2_count_servers.rs");

#[test]
fn aa() {
    assert_eq!(
        Solution::count_servers(
            3,
            vec![vec![1, 3], vec![2, 6], vec![1, 2], vec![2, 1]],
            2,
            vec![3, 6]
        ),
        vec![1, 2]
    );
    assert_eq!(
        Solution::count_servers(
            3,
            vec![vec![2, 6], vec![1, 2], vec![1, 3], vec![2, 1]],
            3,
            vec![10, 5]
        ),
        vec![3, 2]
    );
    assert_eq!(
        Solution::count_servers(2, vec![vec![1, 5], vec![2, 5]], 0, vec![5, 4]),
        vec![0, 2]
    );
}
