impl Solution {
    pub fn stone_game_ii(piles: Vec<i32>) -> i32 {
        let q0 = piles.len();
        let mut q1 = [0i32; 101];
        for a1 in 0..q0 {
            q1[a1 + 1] = q1[a1] + piles[a1];
        }
        let mut q2 = [[0i32; 101]; 101];
        fn dfs(q1: &[i32; 101], q2: &mut [[i32; 101]; 101], a1: usize, a2: usize, a3: usize) -> i32 {
            if a2 * 2 >= a3 - a1 {
                return q1[a3] - q1[a1];
            }
            if q2[a1][a2] != 0 {
                return q2[a1][a2];
            }
            let mut a4 = 0;
            for a5 in 1..=(a2 * 2).min(a3 - a1) {
                a4 = a4.max(q1[a3] - q1[a1] - dfs(q1, q2, a1 + a5, a5.max(a2), a3));
            }
            q2[a1][a2] = a4;
            a4
        }
        dfs(&q1, &mut q2, 0, 1, q0)
    }
}
