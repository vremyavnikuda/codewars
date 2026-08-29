impl Solution {
    pub fn min_bishop_moves(source: Vec<i32>, target: Vec<i32>) -> i32 {
        let aa = source[0].abs_diff(target[0]);
        let bb = source[1].abs_diff(target[1]);
        if aa == 0 && bb == 0 {
            0
        } else if (aa + bb) % 2 != 0 {
            -1
        } else if aa == bb {
            1
        } else {
            2
        }
    }
}
