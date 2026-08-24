impl Solution {
    pub fn stone_game_viii(mut stones: Vec<i32>) -> i32 {
        let q1 = stones.len();
        for q2 in 1..q1 {
            stones[q2] += stones[q2 - 1];
        }
        let mut q3 = stones[q1 - 1];
        for q4 in (1..q1 - 1).rev() {
            q3 = q3.max(stones[q4] - q3);
        }
        q3
    }
}
