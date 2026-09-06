impl Solution {
    pub fn count_groups(position: Vec<i32>, speed: Vec<i32>, distance: i32) -> i32 {
        let mut aa = *speed.last().unwrap();
        let mut bb = 1;
        for cc in (0..position.len() - 1).rev() {
            if position[cc + 1] - position[cc] > distance && speed[cc] <= aa {
                bb += 1;
                aa = speed[cc];
            }
        }
        bb
    }
}
